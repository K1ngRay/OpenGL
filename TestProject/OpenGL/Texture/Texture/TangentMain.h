#pragma once

#include "Project.h"

class Tangent : public Project
{
public:
	Tangent()
	{

	}

	GLFWwindow* CreateWindow(unsigned int width, unsigned int height, GLFWmonitor* monitor, GLFWwindow* share) 
	{
		GLFWwindow* window = glfwCreateWindow(width, height, "Tangent", monitor, share);
		return window;
	}

	void InitCubeVAOWithoutTangent(GLuint &vao, GLuint &vbo) {
		//�󶨲�ʵ�����߿ռ�ͷ�����ͼ��VAOVBO
		float vertices[] = {
			// ����               ����                ��������
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,

			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
			 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f
		};

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	void InitCubeVAOWithTangent(GLuint &vao, GLuint &vbo) {
		//��ʵ�����߿ռ�ͷ�����ͼ��VAOVBO
		float vertices_with_tangent[] = {
			//����                ����                ��������       T
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f, -1.0f,  0.0f,  0.0f,
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f, -1.0f,  0.0f,  0.0f,
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		};
		//TODO:Ϊʲô��ʱ����Ҫ���ߣ���ʱ������
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_with_tangent), vertices_with_tangent, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 6));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 8));
		glEnableVertexAttribArray(3);

	}

	void Render(Shader &withoutShader, Shader &withShader, unsigned int &texture, unsigned int &normal,GLuint &withoutVAO,GLuint &withVAO,Camera &camera) {

		withoutShader.Use();
		glm::mat4 model(1.0f);//���㲢����ɫ������pvm����
		model = glm::translate(model, glm::vec3(-1.0f, 0, 0));
		model = glm::scale(model, glm::vec3(0.5f));
		model = glm::rotate(model, (float)glfwGetTime() * 0.3f, glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1280.0f / 720.0f, 0.1f, 100.0f);
		withoutShader.SetMat4("model", model);
		withoutShader.SetMat4("view", view);
		withoutShader.SetMat4("projection", projection);
		withoutShader.SetVec3("viewPosition", camera.Position);//����������ӽ�λ��

		glm::vec3 directLight = glm::vec3(-0.3f, 0.0f, -1.0f);
		glm::vec3 ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);
		glm::vec3 diffuseLight = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 specularLight = glm::vec3(1.0f, 1.0f, 1.0f);
		withoutShader.SetVec3("directLight", directLight);//���߷���
		withoutShader.SetVec3("ambientLight", ambientLight);//���������
		withoutShader.SetVec3("diffuseLight", diffuseLight);//���������
		withoutShader.SetVec3("specularLight", specularLight);//���淴�����

		glActiveTexture(GL_TEXTURE0); //����ı�ʶΪ0����Ԫ
		glBindTexture(GL_TEXTURE_2D, texture);
		//withoutShader.SetInt("materialTex", 0); //����Ϊ0����GL_TEXTURE0�������Ӷ�ʹtexture��materialTex����

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normal);
		//withoutShader.SetInt("normalTex", 1);

		glBindVertexArray(withoutVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36); //TODO:Ϊ����36
		glBindVertexArray(0);


		//���������߿ռ��ڵķ�����ͼ
		withShader.Use();
		model = glm::mat4(1.0f);//pvm����
		model = glm::translate(model, glm::vec3(1.0f, 0, 0));
		model = glm::scale(model, glm::vec3(0.5f));
		model = glm::rotate(model, (float)glfwGetTime() * 0.3f, glm::vec3(0.5f, 1.0f, 0.0f));
		withShader.SetMat4("model", model);
		withShader.SetMat4("view", view);
		withShader.SetMat4("projection", projection);
		withShader.SetVec3("viewPosition", camera.Position);
		//���߲���
		withShader.SetVec3("directLight", directLight);
		withShader.SetVec3("ambientLight", ambientLight);
		withShader.SetVec3("diffuseLight", diffuseLight);
		withShader.SetVec3("specularLight", specularLight);

		//������������ͷ�����ͼ 
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture);
		//withShader.SetInt("materialTex", 0);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, normal);
		std::cout << glGetError() << "normal" << std::endl;
		//withShader.SetInt("normalTex", 1);

		glBindVertexArray(withVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

private:

};
