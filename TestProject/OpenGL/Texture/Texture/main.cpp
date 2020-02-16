#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>
#include<vector>
#include"stb/stb_image.h"

#include "Camera.h"
#include "Shader.h"
#include "SkyboxMain.h"

using namespace std;
using namespace glm;

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void ProcessInput(GLFWwindow* window);

unsigned int LoadCubeMap(vector<string> faces); //��պм���

const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

Camera camera(vec3(1.0f,0.0f,5.0f));
float lastX = (float)SCREEN_WIDTH / 2.0f, lastY = (float)SCREEN_HEIGHT / 2.0f; // ��������ʼλ��Ϊ��Ļ����
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Skybox project;

	GLFWwindow* window = project.CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL);

	if (window==NULL)
	{
		cout << "Failed to Create Window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to Initialize GLAD" << endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST); //������Ȳ��ԣ���������Ϊֹ����֪��������ô�

	Shader cubeShader("cubemap.vs", "cubemap.fs");
	Shader skyboxShader("skybox.vs", "skybox.fs");

	//��ʼ��VAO��VBO
	GLuint cubeVAO, cubeVBO, skyboxVAO, skyboxVBO;
	project.InitCubeVAO(cubeVAO, cubeVBO);
	project.InitSkyboxVAO(skyboxVAO, skyboxVBO);

	//��ʼ������
	GLuint cubeTexture, skyboxTexture;
	project.InitCubeTexture(cubeTexture);
	project.InitSkyboxTexture(skyboxTexture);

	cubeShader.Use();
	cubeShader.SetInt("texture1", 0);  //��������
	skyboxShader.Use();
	skyboxShader.SetInt("skybox", 0);	//��������

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0); //��ǰû�еģ�Ҫ�úÿ�
		glBindTexture(GL_TEXTURE_2D, cubeTexture);

		cubeShader.Use();

		mat4 model(1);
		model = rotate(model, currentFrame, vec3(0.5f, 1.0f, 0.0f));
		mat4 view(1);
		view = camera.GetViewMatrix();
		mat4 projection(1);
		projection = perspective(radians(camera.Zoom), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

		cubeShader.SetMat4("model", model);
		cubeShader.SetMat4("view", view);
		cubeShader.SetMat4("projection", projection);

		glBindVertexArray(cubeVAO);	//������Ϊʲôuv���ð�
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0); //������������ô�����

		//������������
		glDepthFunc(GL_LEQUAL);//��Ȳ���  ��������ֵС�ڻ���ڲο�ֵ����ͨ��
		glDepthMask(GL_FALSE);//��ֹ����Ȼ�����д������

		skyboxShader.Use();
		view = mat4(mat3(camera.GetViewMatrix()));// remove translation from the view matrix
		skyboxShader.SetMat4("view",view);
		skyboxShader.SetMat4("projection",projection);

		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);//��������Ȼ�����д������
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);//��Ȳ���  ��������ֵС�ڲο�ֵ����ͨ��

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &skyboxVBO);
	glDeleteTextures(1, &cubeTexture);
	glDeleteTextures(1, &skyboxTexture);

	glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Enum_FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Enum_BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Enum_LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Enum_RIGHT, deltaTime);

	//�������¶���
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		// �������
		glEnable(GL_BLEND);
		//���û�ϵ�Դ��Ŀ������
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		// �رջ��
		glDisable(GL_BLEND);
	}
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	camera.ProcessMouseScroll(yOffset);
}
