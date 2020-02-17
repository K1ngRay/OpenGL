#pragma once

#include "Project.h"
#include <vector>

class Skybox : public Project
{
public:
	Skybox() {

	}

	GLFWwindow* CreateWindow(unsigned int width, unsigned int height, GLFWmonitor* monitor, GLFWwindow* share) {
		GLFWwindow* window = glfwCreateWindow(width, height, "Skybox", monitor, share);
		return window;
	}

	void InitCubeVAO(GLuint &vao, GLuint &vbo)
	{
		float vertices[] = { //����������
		   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

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
		   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		   0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		   0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void InitSkyboxVAO(GLuint &vao, GLuint &vbo) {
		float skybox_vertices[] = {   //��պж�������
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			1.0f, -1.0f,  1.0f
		};

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), skybox_vertices, GL_STATIC_DRAW);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void InitCubeTexture(GLuint &texture) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		//TODO��Ҫ�úÿ�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, channels; //������ͨ����
		stbi_set_flip_vertically_on_load(true);  //ʵ�ַ�תy����,��Ϊ OpenGL��������������������½�. ��ͼ���������������������Ͻ�.
		stbi_uc *data = stbi_load("texture/CG_Sprite.jpg", &width, &height, &channels, 0);

		if (data)
		{
			//TODO�����Կ���data�������ʲô,������������ʲô��˼
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

	}

	void InitSkyboxTexture(GLuint &texture) {
		vector<string> faces
		{
			("texture/skybox_snow/right.jpg"),
			("texture/skybox_snow/left.jpg"),
			("texture/skybox_snow/top.jpg"),
			("texture/skybox_snow/bottom.jpg"),
			("texture/skybox_snow/back.jpg"),
			("texture/skybox_snow/front.jpg")
		};

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

		int width, height, channels;
		for (int i = 0; i < faces.size(); i++)
		{
			stbi_set_flip_vertically_on_load(false);	//Ϊʲô����Ͳ�����תy������
			stbi_uc *data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			}
			stbi_image_free(data);
		}
		//TODO���úÿ�
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void Render(Shader &cubeShader,Shader &skyboxShader,GLuint &cubeTex,GLuint &skyboxTex,GLuint &cubeVAO,GLuint &skyboxVAO,Camera &camera) {
		glActiveTexture(GL_TEXTURE0); //��ǰû�еģ�Ҫ�úÿ�
		glBindTexture(GL_TEXTURE_2D, cubeTex);

		cubeShader.Use();

		mat4 model(1);
		model = glm::rotate(model, (float)glfwGetTime(), vec3(0.5f, 1.0f, 0.0f));
		mat4 view(1);
		view = camera.GetViewMatrix();
		mat4 projection(1);
		projection = perspective(radians(camera.Zoom), 1280.0f / 720.0f, 0.1f, 100.0f);

		cubeShader.SetMat4("model", model);
		cubeShader.SetMat4("view", view);
		cubeShader.SetMat4("projection", projection);

		glBindVertexArray(cubeVAO);	//TODO��Ϊʲôuv���ð�
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0); //TODO��������ô�����

		//TODO��������
		glDepthFunc(GL_LEQUAL);//��Ȳ���  ��������ֵС�ڻ���ڲο�ֵ����ͨ��
		glDepthMask(GL_FALSE);//��ֹ����Ȼ�����д������

		skyboxShader.Use();
		view = mat4(mat3(camera.GetViewMatrix()));// remove translation from the view matrix
		skyboxShader.SetMat4("view", view);
		skyboxShader.SetMat4("projection", projection);

		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);//��������Ȼ�����д������
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);//��Ȳ���  ��������ֵС�ڲο�ֵ����ͨ��

	}
};