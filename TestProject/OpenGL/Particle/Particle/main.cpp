#define PARTICLE_ONE 0
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include <algorithm>

// 窗口大小调整的回调函数(当窗口大小改变时，视口也要改变)
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 鼠标控制回调
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// 滚轮控制回调
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// 键盘控制回调
void processInput(GLFWwindow *window);

// 屏幕宽，高
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

float lastX = (float)SCR_WIDTH / 2;
float lastY = (float)SCR_HEIGHT / 2;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

struct Particle {
	glm::vec3 pos, speed;
	unsigned char r, g, b, a;//用char的8位就够了，而且char能表示数字
	float size;
	float life; //生命周期
	float cameraDistance; //粒子和摄像头的距离

	//因为sort的结果是升序，只能判断运算符“<”，所以要将其变成降序，就重载函数的符号写相反
	bool operator< (const Particle& that) const {
		// 逆序排序， 远的粒子排在前面
		return this->cameraDistance > that.cameraDistance; //that 是运算符右侧
	}
};

const int MaxParticles = 500;
const float life = 5.0f;
#if PARTICLE_ONE
glm::vec3 startPos = glm::vec3(0.0f, 0.0f, -5.0f);
glm::vec3 endPos = glm::vec3(0.0f, 0.0f, 5.0f);
#else
const float spread = 3.0f; //粒子扩散程度
#endif
Particle particlesContainer[MaxParticles];

int LastUsedParticle = 0;

int FindUnUsedParticle() {
	for (int i = LastUsedParticle; i < MaxParticles; i++)
	{
		if (particlesContainer[i].life < 0)
		{
			LastUsedParticle = i;
			return i;
		}
	}
	for (int i = 0; i < LastUsedParticle; i++)
	{
		if (particlesContainer[i].life < 0)
		{
			LastUsedParticle = i;
			return i;
		}
	}

	return -1;
}

void SortParticles() {
	std::sort(&particlesContainer[0], &particlesContainer[MaxParticles]);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Particle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to Create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to Initialize GLAD" << std::endl;
		return -1;
	}

	static GLfloat* particle_position_size_data = new GLfloat[MaxParticles * 4];
	static GLubyte* particle_color_data = new GLubyte[MaxParticles * 4];
	for (int i = 0; i < MaxParticles; i++)
	{
		particlesContainer[i].life = -1.0f;
		particlesContainer[i].cameraDistance = -1.0f;
	}
#if PARTICLE_ONE
	GLuint particleTexture = Texture::LoadTextureFromFile("texture/circle.png");
#else 
	GLuint particleTexture = Texture::LoadTextureFromFile("texture/xuehua.png");
#endif

	// 粒子顶点位置
	static const GLfloat g_vertex_buffer_data[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint billboard_VBO;
	glGenBuffers(1, &billboard_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); 
	//"Static”意味着VBO中的数据不会被改变（一次修改，多次使用），"dynamic”意味着数据可以被频繁修改（多次修改，多次使用），"stream”意味着数据每帧都不同（一次修改，一次使用）
	//"Draw”意味着数据将会被送往GPU进行绘制，"read”意味着数据会被用户的应用读取，"copy”意味着数据会被用于绘制和读取
	//注意在使用VBO时，只有draw是有效的，而copy和read主要将会在像素缓冲区（PBO）和帧缓冲区（FBO）中发挥作用。
	
#if !PARTICLE_ONE
	//  粒子的位置和大小
	GLuint particles_position_buffer;
	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);//初始化为NULL，后续根据粒子的属性，进行填充 
	//  包含了粒子的 颜色
	GLuint particles_color_buffer;
	glGenBuffers(1, &particles_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
#else
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
#endif

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

#if PARTICLE_ONE
	Shader shader("particle1.vs", "particle1.fs");
#else
	Shader shader("particle2.vs", "particle1.fs");
#endif // PARTICLE_ONE


	lastFrame = glfwGetTime();
	float addFrame = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		glClearColor(0.0f, 0.13f, 0.15f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::vec3 cameraPosition = camera.Position;
		glm::mat4 PV = projection * view;

		// 消亡多少粒子，产生多少粒子
		addFrame += deltaTime * 0.5f;
		int newParticles = addFrame / life * MaxParticles;
		for (int i = 0; i < newParticles; i++)
		{
			addFrame = 0.0f;
			int particleIndex = FindUnUsedParticle(); //找life等于0的，重复使用
			if (particleIndex == -1) continue;
			particlesContainer[particleIndex].life = life;
			float randomX = (rand() % 1000 - 500.0f) / 500.0f; //[-1,1]
			float randomY = (rand() % 1000 - 500.0f) / 500.0f;
			float randomZ = (rand() % 1000 - 500.0f) / 500.0f;
			glm::vec3 randomOffset = glm::vec3(randomX, randomY, randomZ);

#if PARTICLE_ONE
			particlesContainer[particleIndex].pos = startPos + randomOffset;
			particlesContainer[particleIndex].speed = (endPos - startPos) / life;
#else
			glm::vec3 mainDir = glm::vec3(0.0f, 12.0f, 0.0f);//主要方向
			particlesContainer[particleIndex].pos = glm::vec3(0, -10.0f, -21.0f); //粒子起点
			particlesContainer[particleIndex].speed = mainDir + randomOffset * spread;
#endif
			particlesContainer[particleIndex].r = rand() % 256;
			particlesContainer[particleIndex].g = rand() % 256;
			particlesContainer[particleIndex].b = rand() % 256;
			particlesContainer[particleIndex].a = (rand() % 50) + 50;
#if PARTICLE_ONE
			particlesContainer[particleIndex].size = (rand() % 1000) / 50000.0f + 0.04f; //[0.04, 0.06]
#else
			particlesContainer[particleIndex].size = (rand() % 1000) / 5000.0f + 0.4f; //[0.4, 0.6]
#endif
		}
		//模拟所有的粒子
		//控制life 和 position
		int particlesCount = 0;
		for (int i = 0; i < MaxParticles; i++)
		{
			Particle& p = particlesContainer[i];
			if (p.life > 0.0f)
			{
				p.life -= deltaTime;
				if (p.life > 0.0f)
				{
#if !PARTICLE_ONE
					p.speed += glm::vec3(0.0f, -9.81f, 0.0f) * deltaTime *0.5f;
#endif // !PARTICLE_ONE
					p.pos += p.speed * deltaTime;
					p.cameraDistance = glm::length(p.pos - cameraPosition);
					//储存数据传给着色器使用
					particle_position_size_data[4 * particlesCount + 0] = p.pos.x;
					particle_position_size_data[4 * particlesCount + 1] = p.pos.y;
					particle_position_size_data[4 * particlesCount + 2] = p.pos.z;
					particle_position_size_data[4 * particlesCount + 3] = p.size;
					particle_color_data[4 * particlesCount + 0] = p.r;
					particle_color_data[4 * particlesCount + 1] = p.g;
					particle_color_data[4 * particlesCount + 2] = p.b;
					particle_color_data[4 * particlesCount + 3] = p.a;
				}
				else
					p.cameraDistance = -1.0f; //这样排序会被置于最后

				particlesCount++; //计算当前存活还有多少粒子，这个值用于后面单例渲染的最大索引值
			}
		}

		SortParticles();
#if !PARTICLE_ONE
		//粒子项目二 的修改数据方式
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);  //GL_STREAM_DRAW 将会被送往GPU进行绘制的数据每帧都不同
		//glBufferSubData重新定义当前绑定到target的缓冲区对象的部分或全部数据存储。
		//从字节偏移量offset开始并扩展为size字节的数据从data指向的存储器复制到数据存储器。
		//如果offset和size一起定义超出缓冲区对象的数据存储边界的范围，则抛出错误。
		glBufferSubData(GL_ARRAY_BUFFER, 0, particlesCount * 4 * sizeof(GLfloat), particle_position_size_data); 
		//glBufferData(GL_ARRAY_BUFFER, particlesCount * 4 * sizeof(GLfloat), particle_position_size_data, GL_STREAM_DRAW); //不写glBufferSubData的话，写这句也可以

		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, particlesCount * sizeof(GLubyte) * 4, particle_color_data);
		//glBufferData(GL_ARRAY_BUFFER, particlesCount * 4 * sizeof(GLfloat), particle_color_data, GL_STREAM_DRAW);
#endif // !PARTICLE_ONE


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		shader.Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, particleTexture);
		shader.SetInt("myTextureSampler", 0);

		//摄像机的右方向
		shader.SetVec3("CameraRight_worldspace", view[0][0], view[1][0], view[2][0]); //[0][0]表示本地坐标的x轴方向在世界坐标x轴上的分量，[0][1]以此类推
		//摄像机的上方向
		shader.SetVec3("CameraUp_worldspace", view[0][1], view[1][1], view[2][1]);
		shader.SetMat4("PV", PV);

#if PARTICLE_ONE
		//粒子项目一 的修改数据方式
		glBindVertexArray(VAO);
		for (int i = 0; i < particlesCount; i++)
		{
			shader.SetVec4("xyzs", particle_position_size_data[4 * i + 0],
				particle_position_size_data[4 * i + 1],
				particle_position_size_data[4 * i + 2],
				particle_position_size_data[4 * i + 3]);
			shader.SetVec4("color", particle_color_data[4 * i + 0],
				particle_color_data[4 * i + 1],
				particle_color_data[4 * i + 2],
				particle_color_data[4 * i + 3]);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //GL_TRIANGLE_STRIP 可以少传一个点
		}
#else
		// 粒子的顶点坐标
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, billboard_VBO); //由于前面的顶点缓冲对象被绑定成其他，所以需要绑回来
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); //stride是0意味着stride为size(第二个参数)*type(第三个参数)

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0); 

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, (void*)0); //因为要传rgba，所以normalize可以为GL_TRUE,而设置为GL_FALSE的话，在着色器中就需要除以256
		
		glVertexAttribDivisor(0, 0);// 粒子顶点坐标 : 总是重用相同的 4 个顶点坐标，所以第二个参数是 0
		//之前渲染的都是相同的对象，所以VAO的内容都是基本相同的
		//本项目让OpenGL自主递增渲染，所以需要告诉OpenGL VAO里的内容是会变的
		//glVertexAttribDivisor的第一个参数是index，第二个参数是告诉OpenGL VAO的内容是否变化，若变化，则按照 索引*缓冲区偏移量 找到下一个数据
		glVertexAttribDivisor(1, 1);// 粒子的中心位置和大小，每一个粒子不同，所以第二个参数是 1
		glVertexAttribDivisor(2, 1);// 粒子的颜色，每一个粒子不同，所以第二个参数是 1

		//这句跟上面结合，按照单例渲染
		//相对glDrawArrays，多了instancecount这个参数，这个参数就是单例数量，Opengl向后索引数据的最大索引值
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particlesCount);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
#endif // PARTICLE_ONE

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete[] particle_position_size_data;
	delete[] particle_color_data;

	glDeleteBuffers(1, &billboard_VBO);
#if !PARTICLE_ONE
	glDeleteBuffers(1, &particles_position_buffer);
	glDeleteBuffers(1, &particles_color_buffer);
#endif
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shader.ID);
	glDeleteTextures(1, &particleTexture);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

//是如何让粒子消失的
/*
在模拟粒子运动时，计算存活（life>0）的粒子的数量particlesCount
最后再调用渲染单例，让OpenGL根据particlesCount自动渲染当前存活的粒子
当life=0时，将其cameraDistance置为-1，调用数据排序，将其粒子放在数组的后部，而存放位置和颜色的数组的内容也会被替换掉
当particlesCount为0时，表示没有存活的粒子，OpenGL也就渲染0次，故不会渲染粒子，从而达到粒子消失的效果
*/