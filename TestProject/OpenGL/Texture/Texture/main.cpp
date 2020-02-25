#define SWITCH_BIT 2

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>
#include<string>

#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "SkyboxMain.h"
#include "TangentMain.h"
#include "Shadow.h"

using namespace std;
using namespace glm;

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void ProcessInput(GLFWwindow* window);

const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

Camera camera(vec3(0.0f,0.0f,3.0f));
float lastX = (float)SCREEN_WIDTH / 2.0f, lastY = (float)SCREEN_HEIGHT / 2.0f; // 设置鼠标初始位置为屏幕中心
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if SWITCH_BIT == 0
	Skybox project;
#elif SWITCH_BIT == 1
	Tangent project;
#elif SWITCH_BIT  == 2
	Shadow project;
#endif
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

	glEnable(GL_DEPTH_TEST); //开启深度测试，但到现在为止还不知道具体的用处

	Texture textureClass;
#if SWITCH_BIT == 0
	Shader cubeShader("cubemap.vs", "cubemap.fs");
	if (!cubeShader.success) return 0;
	Shader skyboxShader("skybox.vs", "skybox.fs");
	if (!skyboxShader.success) return 0;

	//初始化VAO和VBO
	GLuint cubeVAO, cubeVBO, skyboxVAO, skyboxVBO;
	project.InitCubeVAO(cubeVAO, cubeVBO);
	project.InitSkyboxVAO(skyboxVAO, skyboxVBO);

	//初始化纹理
	GLuint cubeTexture, skyboxTexture;
	vector<string> faces
	{
		("texture/skybox_snow/right.jpg"),
		("texture/skybox_snow/left.jpg"),
		("texture/skybox_snow/top.jpg"),
		("texture/skybox_snow/bottom.jpg"),
		("texture/skybox_snow/back.jpg"),
		("texture/skybox_snow/front.jpg")
	};

	//project.InitCubeTexture(cubeTexture);
	//project.InitSkyboxTexture(skyboxTexture);
	cubeTexture = textureClass.LoadTextureFromFile("texture/CG_Sprite.jpg");
	skyboxTexture = textureClass.LoadTexturesFromFile(faces);

	cubeShader.Use();
	cubeShader.SetInt("texture1", 0);  //传入纹理
	skyboxShader.Use();
	skyboxShader.SetInt("skybox", 0);	//传入纹理
#elif SWITCH_BIT == 1
	Shader withoutShader("normal.vs", "normal.fs");
	if (!withoutShader.success) 
		return 0;
	Shader withShader("normalTangent.vs", "normalTangent.fs");
	if (!withShader.success) 
		return 0;

	//初始化VAO和VBO
	GLuint withoutVAO, withoutVBO, withVAO, withVBO;
	project.InitCubeVAOWithoutTangent(withoutVAO, withoutVBO);
	project.InitCubeVAOWithTangent(withVAO, withVBO);

	//初始化纹理
	GLuint texture, normal;
	texture = textureClass.LoadTextureFromFile("texture/cube_diffuse.jpg");
	normal = textureClass.LoadTextureFromFile("texture/cube_normal.jpg");
#elif SWITCH_BIT  == 2
	Shader sceneShader = Shader("DrawScene.vs", "DrawScene.fs");
	Shader shadowMapShader = Shader("shadowMap.vs", "shaderMap.fs");
	Shader debugQuadShader = Shader("debugDepthQuad.vs", "debugDepthQuad.fs");

	GLuint sceneVAO, sceneVBO, planeVAO, planeVBO, depthMapFBO, depthMap;
	vec2 resolution = vec2(1024, 1024);
	project.InitFBOAndTexture(depthMapFBO, depthMap,resolution.x,resolution.y);
	project.InitSceneVAO(sceneVAO, sceneVBO);
	project.InitPlaneVAO(planeVAO, planeVBO); //TODO:可以和上面换换试试

	//纹理载入
	sceneShader.Use();//todo:如果没有glDrawArrays(),这个use()有什么用
	unsigned int diffuseMap, floor;
	diffuseMap = Texture::LoadTextureFromFile("texture/container2.jpg");
	floor = Texture::LoadTextureFromFile("texture/floor2.jpg");
	sceneShader.SetInt("diffuseTexture", 0);
	sceneShader.SetInt("depthMap", 1);

	//TODO:下面开始神仙操作了
	GLfloat near_plane = 1.0f, far_plane = 7.5f;  // 视锥的远近平面
	vec3 lightPos(-3.0f, 4.0f, -1.0f);

	mat4 lightProjection = ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);// 正交投影
	mat4 lightView = lookAt(lightPos, vec3(0), vec3(0.0f, 1.0f, 0.0f));// 从光源的位置看向场景中央
	mat4 lightPV = lightProjection * lightView;

	debugQuadShader.Use();
	debugQuadShader.SetInt("shadowMap", 0);
#endif

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if SWITCH_BIT == 0
		project.Render(cubeShader, skyboxShader, cubeTexture, skyboxTexture,cubeVAO, skyboxVAO,camera);
#elif SWITCH_BIT == 1
		//todo:是如何根据法线控制表面纹理的明暗处理的
		project.Render(withoutShader, withShader, texture, normal, withoutVAO, withVAO, camera);
#elif SWITCH_BIT == 2

#endif

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
#if SWITCH_BIT == 0
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &skyboxVBO);
	glDeleteTextures(1, &cubeTexture);
	glDeleteTextures(1, &skyboxTexture);
#elif SWITCH_BIT == 1
	glDeleteVertexArrays(1, &withoutVAO);
	glDeleteVertexArrays(1, &withVAO);
	glDeleteBuffers(1, &withVBO);
	glDeleteBuffers(1, &withVAO);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &normal);
#elif SWITCH_BIT == 2
#endif
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

	//TODO：新东西
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
