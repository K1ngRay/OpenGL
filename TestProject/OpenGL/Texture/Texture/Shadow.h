#pragma once
#include "Project.h"
#include <glad/glad.h>
class Shadow : public Project
{
public:
	Shadow() {}

	GLFWwindow* CreateWindow(unsigned int width, unsigned int height, GLFWmonitor* monitor, GLFWwindow* share) {
		GLFWwindow* window = glfwCreateWindow(width, height, "Shadow", monitor, share);
		return window;
	}

	void InitSceneVAO(GLuint &vao, GLuint &vbo) {
		// ������
		float cubeVertices[] = {
			//  ---- λ�� ----       ---- ���� ----   - �������� -
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
			1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.5f, 0.0f,
			1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f,

			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
			1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.5f, 0.0f,
			1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.5f, 0.5f,
			1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.5f, 0.5f,
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.5f,
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.5f, 0.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.5f, 0.5f,
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f,
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f,
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.5f, 0.0f,

			1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.5f, 0.0f,
			1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f,
			1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.5f, 0.5f,
			1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f,
			1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.5f, 0.0f,
			1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f,
			1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.5f, 0.5f,
			1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.5f, 0.0f,
			1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.5f, 0.0f,
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f,

			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f,
			1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 0.5f, 0.0f,
			1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.5f, 0.5f,
			1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.5f, 0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f,
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f
		};

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
	
	//TODO:���vao�����ĸ�shader��ѽ
	void InitPlaneVAO(GLuint &vao, GLuint &vbo) {
		//�ذ�����
		float planeVertices[] = {
			5.0f, -0.5f,  5.0f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
			-5.0f, -0.5f,  5.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

			5.0f, -0.5f,  5.0f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
			5.0f, -0.5f, -5.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f
		};

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	//TODO:����FBO�Ǹ������
	//����������Ⱦ֡����(���������ͼ)
	void InitFBOAndTexture(GLuint &fbo,GLuint &texture,int width,int height) {
		glGenFramebuffers(1, &fbo);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		//TODO:��ʼ������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//�������Խ��
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Render(Shader &sceneShader,Shader &shadowMapShader,Shader &debugQuadShader, GLuint &sceneVao,GLuint &planeVao,GLuint FBO) {

	}

private:

};
