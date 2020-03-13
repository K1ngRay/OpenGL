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

// ���ڴ�С�����Ļص�����(�����ڴ�С�ı�ʱ���ӿ�ҲҪ�ı�)
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// �����ƻص�
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// ���ֿ��ƻص�
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// ���̿��ƻص�
void processInput(GLFWwindow *window);

// ��Ļ����
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
	unsigned char r, g, b, a;//��char��8λ�͹��ˣ�����char�ܱ�ʾ����
	float size;
	float life; //��������
	float cameraDistance; //���Ӻ�����ͷ�ľ���

	bool operator< (const Particle& that) const {
		// �������� Զ����������ǰ��
		return this->cameraDistance > that.cameraDistance; //д���������﷨Ҫȥѧϰһ��
	}
};

const int MaxParticles = 500;
const float life = 5.0f;
#if PARTICLE_ONE
glm::vec3 startPos = glm::vec3(0.0f);
glm::vec3 endPos = glm::vec3(0.0f, 0.0f, 4.8f);
#else
const float spread = 3.0f; //������ɢ�̶�
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

	// ���Ӷ���λ��
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); //TODO:���GL_STATIC_DRAW
	
#if !PARTICLE_ONE
	//  ���ӵ�λ�úʹ�С
	GLuint particles_position_buffer;
	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);//��ʼ��ΪNULL�������������ӵ����ԣ�������� //TODO:GL_STREAM_DRAW �¶���
	//  ���������ӵ� ��ɫ
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

		// �����������ӣ�������������
		int newParticles = deltaTime / life * MaxParticles; //TODO:�����⹫ʽ������

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
			glm::vec3 mainDir = glm::vec3(0.0f, 12.0f, 0.0f);//��Ҫ����
			particlesContainer[particleIndex].pos = glm::vec3(0, -10.0f, -20.0f); //�������
			particlesContainer[particleIndex].speed = mainDir + randomOffset * spread;
#endif
			particlesContainer[particleIndex].r = rand() % 256;
			particlesContainer[particleIndex].g = rand() % 256;
			particlesContainer[particleIndex].b = rand() % 256;
			particlesContainer[particleIndex].a = (rand() % 100) + 50;
			particlesContainer[particleIndex].size = (rand() % 1000) / 5000.0f + 0.4f; //[0.4, 0.6]
		}

		//ģ�����е�����
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
					//�������
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
		glBufferSubData(GL_ARRAY_BUFFER, 0, particlesCount * 4 * sizeof(GLfloat), particle_position_size_data); //TODO:����ʲô

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

		//��������ҷ���
		shader.SetVec3("CameraRight_worldspace", view[0][0], view[1][0], view[2][0]);
		//��������Ϸ���
		shader.SetVec3("CameraUp_worldspace", view[0][1], view[1][1], view[2][1]); //TODO:��Ҫ�˽�һ��view������ڲ�����
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
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //GL_TRIANGLE_STRIP �����ٴ�һ����
		}
#else
		shader.SetBool("isParticleOne", false);

		// ���ӵĶ�������
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, billboard_VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); //todo��Ϊʲôstride��0

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0); //TODO:�е����

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0); //TODO:normalize ����Ϊtrue��
		
		//todo:�úÿ�
		glVertexAttribDivisor(0, 0);// ���Ӷ������� : ����������ͬ�� 4 ���������꣬���Եڶ��������� 0
		glVertexAttribDivisor(1, 1);// ���ӵ�����λ�úʹ�С��ÿһ�����Ӳ�ͬ�����Եڶ��������� 1
		glVertexAttribDivisor(2, 1);// ���ӵ���ɫ��ÿһ�����Ӳ�ͬ�����Եڶ��������� 1

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

//todo:�������������ʧ��