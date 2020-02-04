//总体流程
//1. 初始化并创建窗口
//2. 加载立方体顶点VAOVBO以及着色器并开启深度测试
//3. 进入主循环清除缓冲
//4. 使用立方体着色器，构造并传入pvm矩阵，绘制
//5. 循环结束，释放VAOVBO

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "camera.h"
#define USE_CAMERA true;

using namespace std;

//鼠标键盘响应函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window,float deltaTime);

const float vertices[] = {                  //立方体数组,六个面，六种颜色
	-0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,0.0f,0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,0.0f,0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f,0.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,1.0f,0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,1.0f,0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,1.0f,0.0f,

	-0.5f,  0.5f,  0.5f,  0.0f,0.0f,1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,0.0f,1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,0.0f,1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,0.0f,1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,0.0f,1.0f,

	0.5f,  0.5f,  0.5f,  0.5f,0.0f,0.0f,
	0.5f,  0.5f, -0.5f,  0.5f,0.0f,0.0f,
	0.5f, -0.5f, -0.5f,  0.5f,0.0f,0.0f,
	0.5f, -0.5f, -0.5f,  0.5f,0.0f,0.0f,
	0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.0f,
	0.5f,  0.5f,  0.5f,  0.5f,0.0f,0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f,0.5f,0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,0.5f,0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,0.5f,0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,0.5f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,0.5f,0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,0.5f,0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,0.0f,0.5f,
	0.5f,  0.5f, -0.5f,  0.0f,0.0f,0.5f,
	0.5f,  0.5f,  0.5f,  0.0f,0.0f,0.5f,
	0.5f,  0.5f,  0.5f,  0.0f,0.0f,0.5f,
	-0.5f,  0.5f,  0.5f,  0.0f,0.0f,0.5f,
	-0.5f,  0.5f, -0.5f,  0.0f,0.0f,0.5f
};

//窗口参数
int screen_width = 1280;
int screen_height = 720;
//相机参数
glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 3.0f);     //摄像机位置
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);       //摄像机方向
glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);           //摄像机上向量
//视野
float fov = 45.0f;

//摄像机
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = screen_width / 2.0f;
float lastY = screen_height / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	auto window = glfwCreateWindow(screen_width, screen_height, "Cube", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "Failed to Create Window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  //这个要查查

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to Initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, screen_width, screen_height);

	Shader shader("vertexShader.vsh", "fragmentShader.fsh");

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0); //第一个参数对应vertexShader里“layout(location = 0)”的变量，最后一个变量对应VAO的缓存偏移值
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{

		//计算deltaTime
		float curFrame = glfwGetTime();
		deltaTime = curFrame - lastFrame;
		lastFrame = curFrame;
		processInput(window, deltaTime);

		glClearColor(0.0f, 0.34f, 0.57f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();

		//Transform 坐标变换矩阵
		glm::mat4 model(1);//构造函数，创建一个单位矩阵，model矩阵，局部坐标转换至世界坐标
		model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f)); //需要旋转模型，角度，旋转轴
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glm::mat4 view(1);//view矩阵，世界坐标转换至观察坐标系
#if !USE_CAMERA
		view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);
#endif
		view = camera.GetViewMatrix();
		glm::mat4 projection(1);//projection矩阵，投影矩阵
#if !USE_CAMERA
		projection = glm::perspective(glm::radians(fov), (float)screen_width / screen_height, 0.1f, 100.0f); //第一个参数为视锥上下面之间的夹角，第二个参数为宽高比，即视窗的宽/高，第三第四个参数分别为近截面和远界面的深度
#endif
		projection = glm::perspective(glm::radians(camera.Zoom), (float)screen_width / screen_height, 0.1f, 100.0f);

		// 向着色器中传入参数
		//int model_location = glGetUniformLocation(shader.ID, "model");////获取着色器内某个参数的位置
		//glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model)); //给矩阵赋值
		shader.SetMat4("model", model);
		//int view_location = glGetUniformLocation(shader.ID, "view");
		//glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
		shader.SetMat4("view", view);
		//int projection_location = glGetUniformLocation(shader.ID, "projection");
		//glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));
		shader.SetMat4("projection", projection);

		//绘制
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window,float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow *windows,int width,int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = xpos - lastX;
	float yOffset = ypos - lastY;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}