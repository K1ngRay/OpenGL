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

	bool operator< (const Particle& that) const {
		// 逆序排序， 远的粒子排在前面
		return this->cameraDistance > that.cameraDistance; //写操作符的语法要去学习一下
	}
};

const int MaxParticles = 500;
const float life = 5.0f;
#if PARTICLE_ONE
glm::vec3 startPos = glm::vec3(0.0f);
glm::vec3 endPos = glm::vec3(0.0f, 0.0f, 4.8f);
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

	return 0;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); //TODO:查查GL_STATIC_DRAW
	
#if !PARTICLE_ONE
	//  粒子的位置和大小
	GLuint particles_position_buffer;
	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);//初始化为NULL，后续根据粒子的属性，进行填充 //TODO:GL_STREAM_DRAW 新东西
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
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.0f, 0.13f, 0.15f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::vec3 cameraPosition = camera.Position;
		glm::mat4 PV = projection * view;

		// 消亡多少粒子，产生多少粒子
		int newParticles = deltaTime / life * MaxParticles; //TODO:不懂这公式哪来的

		for (int i = 0; i < newParticles; i++)
		{
			int particleIndex = FindUnUsedParticle();
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
			particlesContainer[particleIndex].pos = glm::vec3(0, -10.0f, -20.0f); //粒子起点
			particlesContainer[particleIndex].speed = mainDir + randomOffset * spread;
#endif
			particlesContainer[particleIndex].r = rand() % 256;
			particlesContainer[particleIndex].g = rand() % 256;
			particlesContainer[particleIndex].b = rand() % 256;
			particlesContainer[particleIndex].a = (rand() % 100) + 50;
			particlesContainer[particleIndex].size = (rand() % 1000) / 5000.0f + 0.4f; //[0.4, 0.6]
		}

		//模拟所有的粒子
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
					//填充数据
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
					p.cameraDistance = -1.0f;

				particlesCount++;
			}
		}

		SortParticles();
#if !PARTICLE_ONE
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, particlesCount * 4 * sizeof(GLfloat), particle_position_size_data); //TODO:这是什么

		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, particlesCount * sizeof(GLubyte) * 4, particle_color_data);
#endif // !PARTICLE_ONE


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		shader.Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, particleTexture);
		shader.SetInt("myTextureSampler", 0);

		//摄像机的右方向
		shader.SetVec3("CameraRight_worldspace", view[0][0], view[1][0], view[2][0]);
		//摄像机的上方向
		shader.SetVec3("CameraUp_worldspace", view[0][1], view[1][1], view[2][1]); //TODO:需要了解一下view矩阵的内部意义
		shader.SetMat4("PV", PV);

#if PARTICLE_ONE
		shader.SetBool("isParticleOne", true);
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
		shader.SetBool("isParticleOne", false);

		// 粒子的顶点坐标
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, billboard_VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); //todo：为什么stride是0

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0); //TODO:有点奇怪

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0); //TODO:normalize 终于为true了
		
		//todo:好好看
		glVertexAttribDivisor(0, 0);// 粒子顶点坐标 : 总是重用相同的 4 个顶点坐标，所以第二个参数是 0
		glVertexAttribDivisor(1, 1);// 粒子的中心位置和大小，每一个粒子不同，所以第二个参数是 1
		glVertexAttribDivisor(2, 1);// 粒子的颜色，每一个粒子不同，所以第二个参数是 1

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

//todo:是如何让粒子消失的