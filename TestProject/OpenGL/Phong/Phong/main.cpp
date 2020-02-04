#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <sstream>
#include "Camera.h"
#include "Light.h"
#include "Shader.h"

using namespace std;
using namespace glm;

float WIDTH = 1280.0f;
float HEIGHT = 720.0f;

float deltaTime = 0.0f;
float lastTime = 0.0f;

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;

unsigned int lightBits = 0;

Camera camera = Camera(vec3(0.0f, 0.0f, 3.0f));

// 顶点数据																 
float vertices[] = {
	// ---- 位置 ----       ---- 法线 ----   
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

// 点光源位置
glm::vec3 pointLightPoses[] = {
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.5f, 0.0f),
	glm::vec3(0.0f, 0.0f, 2.0f),
	glm::vec3(0.0f, -2.5f, 0.0f),
	glm::vec3(0.0f, 0.0f, -3.0f),
	glm::vec3(-3.5f, 0.0f, 0.0f)
};

// 光源颜色
glm::vec3 lightColors[] = {
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.5f, 0.5f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 0.5f, 0.5f),
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, 0.0f, 0.5f)
};

void ProcessInput(GLFWwindow* window);
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
bool IsLightOn(int index);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Light Show", nullptr, nullptr);
	if (window == NULL)
	{
		cout << "Create Windows Failed" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetKeyCallback(window, KeyCallback);

	//初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Load GLAD Failed" << endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	camera.flip_y = true;

	//着色器
	Shader lampShader = Shader("DrawLamp.vs", "DrawLamp.fs");
	Shader cubeShader = Shader("DrawCube.vs", "DrawCube,fs");

	//设置光源
	DirectLight dirLight = DirectLight(vec3(-0.2f, -1.0f, -0.3f), vec3(0.05f), vec3(0.4f), vec3(0.5f));

	PointLight pointLights[6];
	for (int i = 0; i < 6; i++)
	{
		pointLights[i] = PointLight(pointLightPoses[i], 0.05f*lightColors[i], 0.8f*lightColors[i], lightColors[i]);
	}

	SpotLight spotLight = SpotLight(camera.position, camera.forward, vec3(0.0f), vec3(1.0f), vec3(1.0f),
		1.0f, 0.09f, 0.032f, cos(radians(12.5f)), cos(radians(15.0f)));

	//绑定VAO,VBO
	unsigned int vbo, lamp_vao, cube_vao;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &lamp_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(lamp_vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenVertexArrays(1, &cube_vao);
	glBindVertexArray(cube_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);	//这句的位置可以调换一下上下看看效果
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		float curFrame = glfwGetTime();
		deltaTime = curFrame - lastTime;
		lastTime = glfwGetTime();

		ProcessInput(window);

		glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 view = camera.GetViewMatrix();
		mat4 projection = perspective(radians(camera.zoom), WIDTH / HEIGHT, 0.1f, 100.0f);

		//设置立方体材质
		cubeShader.Use();
		cubeShader.SetVec3("viewPos", camera.position); //看不懂
		cubeShader.SetFloat("material.shinness", 32.0f);
		cubeShader.SetVec3("material.diffuse", vec3(0.0f, 0.5f, 0.5f));
		cubeShader.SetVec3("material.specular", vec3(0.5f));

		dirLight.SetActive(IsLightOn(0));	//看不懂
		dirLight.Draw(cubeShader, "dirLight");

		for (int i = 0; i < 6; i++)
		{
			stringstream name_stream;
			name_stream << "pointLight[" << i << "]";
			string name = name_stream.str();
			pointLights[i].SetActive(IsLightOn(i));
			pointLights[i].Draw(cubeShader, name);
		}

		spotLight.SetActive(IsLightOn(7));
		spotLight.SetPosition(camera.position);
		spotLight.SetDirection(camera.forward);
		spotLight.Draw(cubeShader, "spotLight");

		cubeShader.SetMat4("projection", projection);
		cubeShader.SetMat4("view", view);

		//绘制立方体
		glBindVertexArray(cube_vao);
		mat4 model = mat4(1.0f);
		cubeShader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//绘制灯
		glBindVertexArray(lamp_vao);
		for (int i = 0; i < 6; i++)
		{
			if (IsLightOn(i + 1))
			{
				mat4 model = mat4(1.0f);
				model = translate(model, pointLightPoses[i]);
				//model = scale(model, vec3(0.2f, 0.2f, 0.2f));
				lampShader.SetMat4("model", model);
				lampShader.SetVec3("lightColor", lightColors[i]);
				glDrawArrays(GL_TRIANGLES, 0, 36); //为什么是36
			}
		}
		glfwSwapBuffers(window);
		glfwPollEvents();//忘了这句是干嘛的了
	}

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &cube_vao);
	glDeleteVertexArrays(1, &lamp_vao);

	glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow* window) {
	float speed = camera.mouse_speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.Move(camera.forward*speed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.Move(-camera.forward*speed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.Move(-camera.right*speed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.Move(camera.right*speed);
}

// 窗口大小调整的回调函数(当窗口大小改变时，视口也要改变)
// 不知道哪里用得到
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, true); break;
		case GLFW_KEY_1: lightBits ^= 1; break;
		case GLFW_KEY_2: lightBits ^= (1 << 1); break;
		case GLFW_KEY_3: lightBits ^= (1 << 2); break;
		case GLFW_KEY_4: lightBits ^= (1 << 3); break;
		case GLFW_KEY_5: lightBits ^= (1 << 4); break;
		case GLFW_KEY_6: lightBits ^= (1 << 5); break;
		case GLFW_KEY_7: lightBits ^= (1 << 6); break;
		case GLFW_KEY_8: lightBits ^= (1 << 7); break;
		default:
			break;
		}
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos) {
	float xOffset = xPos - lastX;	// 计算当前帧与上一帧的鼠标位置偏移量
	float yOffset = yPos - lastY;
	lastX = xPos;
	lastY = yPos;

	float sensitivity = 0.1;	// 灵敏度*偏移量，避免鼠标移动太大
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	camera.Rotate(vec3(xOffset, yOffset, 0));
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	camera.Zoom(yOffset);
}

bool IsLightOn(int index) {
	return (lightBits >> index) & 1;
}