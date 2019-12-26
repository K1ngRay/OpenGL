#include "shader.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <vector>
#include <math.h>
#include <malloc.h>
using namespace std;

const unsigned int screenWidth = 780;
const unsigned int screenHeight = 780;
const GLfloat PI = 3.14159265358979323846f;

const int Y_SEGMENTS = 50;
const int X_SEGMENTS = 50;
typedef struct GLFWwindow GLFWwindow;

int main() {
	GLFWwindow* CreateWindow(int width, int height,int* success);
	int success;
	auto window = CreateWindow(screenWidth, screenHeight,&success);
	if (!success) {
		return -1;
	}

	Shader shader("VertexShader.vs", "FragmentShader.fs");

	vector<float> sphereVertices;
	vector<int> sphereIndices;

	for (int y = 0; y <= Y_SEGMENTS; y++)
	{
		for (int x = 0; x <= X_SEGMENTS; x++)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = cos(xSegment * 2.0f * PI) * sin(ySegment * PI);
			float yPos = cos(ySegment * PI);
			float zPos = sin(xSegment * 2.0f * PI) * sin(ySegment * PI);

			sphereVertices.push_back(xPos);
			sphereVertices.push_back(yPos);
			sphereVertices.push_back(zPos);
		}
	}
	
	/*	可以理解为经纬度
	*	i为纬度，j为经度
	*	假设i=1，j=5
	*	即纬度1/Y_SEGMENT度上的经度5/X_SEGMENT度
	*********************************************
	*	写EBO的原因在于，上面的VBO都是横向的点（类似在纬度上的点）
	*	没办法形成三角形
	*	故根据三角形的原则，使用EBO将VBO的点进行索引查找
	*	再将这些点传给着色器渲染
	*/
	for (int i = 0; i < Y_SEGMENTS; i++)
	{
		for (int j = 0; j < X_SEGMENTS; j++)
		{
			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);				//左上
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j);		//右上
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);	//右下

			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);				//左上
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);	//右下
			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j + 1);			//左下
		}
	}

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), &sphereVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO); //在EBO这块地址上创建一个缓冲区
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(int), &sphereIndices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //线框模式
	//glPointSize(5); //点阵模式
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, X_SEGMENTS*Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	glfwTerminate();

	return 0;
}

GLFWwindow* CreateWindow(int width, int height,int* success) {
	*success = 1;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	auto window = glfwCreateWindow(width, height, "Sphere", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "Failed to Create OpenGL Context" << endl;
		glfwTerminate();
		*success = 0;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		*success = 0;
	}

	glViewport(0, 0, width, height);
	return window;
}