/*
透明混合要注意两点：1.开启混合；2.透明的物体要根据深度由远到近渲染
*/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include "Camera.h";
#include "Shader.h"
#include "Texture.h"

using namespace std;

// 窗口大小调整的回调函数(当窗口大小改变时，视口也要改变)
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 鼠标控制回调
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// 滚轮控制回调
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// 键盘控制回调
void processInput(GLFWwindow *window);

const int SCREEN_WIDTH = 1280;
const int SCRENN_HEIGHT = 720;

Camera camera(glm::vec3(1.0f, 0.0f, 5.0f)); //摄像机位置
float lastX = (float)SCREEN_WIDTH / 2.0, lastY = (float)SCRENN_HEIGHT / 2.0; // 设置鼠标初始位置为屏幕中心
bool firstMouse = true;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCRENN_HEIGHT, "Blending", NULL, NULL);

	if (window == NULL)
	{
		cout << "Failed to Create GLFW Window" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to Initialize GLAD" << endl;
		return -1;
	}

	//开启深度测试
	glEnable(GL_DEPTH_TEST);
	//开启混合
	glEnable(GL_BLEND);
	//设置混合的源和目标因子,源色可以理解位于前面的透明物体颜色，目标色是位于后面的物体颜色
	//这个函数可以源色和目标色各自的颜色取出，乘以一个系数，得出新的源色和新的目标色，然后两个颜色相加就得到混合的颜色了
	//glBlendFunc(GL_ONE, GL_ZERO);        // 源色将覆盖目标色，源色的系数为1，目标色的系数为0，所以最终得到的只有源色的颜色
	//glBlendFunc(GL_ZERO, GL_ONE);        // 目标色将覆盖源色，源色的系数为0，目标色的系数为1
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //源色的系数为源色的alpha值，目标色的系数为（1-源色的alpha值）


	Shader shader("blending.vs", "blending.fs");

	// 顶点数据
	float cubeVertices[] = {

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f
	};
	// 顶点数据
	float planeVertices[] = {
		 5.0f, -0.5f,  5.0f,  20.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 20.0f,

		 5.0f, -0.5f,  5.0f,  20.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 20.0f,
		 5.0f, -0.5f, -5.0f,  20.0f, 20.0f
	};
	// 顶点数据
	float transparentVertices[] = {
		 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		 0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		 1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		 
		 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		 1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		 1.0f,  0.5f,  0.0f,  1.0f,  0.0f
	};

	// 箱子 VAO
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// 地板 VAO
	unsigned int planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// 透明window VAO
	unsigned int transparentVAO, transparentVBO;
	glGenVertexArrays(1, &transparentVAO);
	glGenBuffers(1, &transparentVBO);
	glBindVertexArray(transparentVAO);
	glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	//纹理
	unsigned int cubeTexture = Texture::LoadTextureFromFile("texture/cube.jpg");
	unsigned int floorTexture = Texture::LoadTextureFromFile("texture/TexturesCom_WoodFine0032_2_seamless_S.jpg");
	unsigned int transparentTexture = Texture::LoadTextureFromFile("texture/window.png");

	// 透明window的位置
	vector<glm::vec3> windows
	{
		glm::vec3(-1.5f, 0.0f, -0.48f),
		glm::vec3(2.5f, 0.0f, 0.51f),
		glm::vec3(0.0f, 0.0f, 0.7f),
		glm::vec3(-0.3f, 0.0f, -2.3f),
		glm::vec3(0.5f, 0.0f, -0.6f)
	};

	shader.Use();
	shader.SetInt("texture1", 0);

	lastFrame = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = glfwGetTime();

		processInput(window);

		//计算摄像机位置向量和物体的位置向量之间的距离
		//map会自动根据键值(Key)对它的值排序，所以只要我们添加了所有的位置，并以它的距离作为键，它们就会自动根据距离值排序了
		map<float, glm::vec3> sorted;
		for (unsigned int i = 0; i < windows.size(); i++)
		{
			float distance = glm::length(camera.Position - windows[i]);
			sorted[distance] = windows[i];
		}

		glClearColor(0.0f, 0.22f, 0.36f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		shader.Use();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCRENN_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model(1.0f);
		shader.SetMat4("projection", projection);
		shader.SetMat4("view", view);

		//绘制箱子
		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, -1.0f));
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//绘制地板
		glBindVertexArray(planeVAO);
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		model = glm::mat4(1.0f);
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//绘制透明window
		glBindVertexArray(transparentVAO);
		glBindTexture(GL_TEXTURE_2D, transparentTexture);
		for (std::map<float,glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, it->second); //first 是取key， second 是取value
			shader.SetMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &planeVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &planeVBO);

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
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		// 开启混合
		glEnable(GL_BLEND);
		//设置混合的源和目标因子
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		// 关闭混合
		glDisable(GL_BLEND);
	}
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