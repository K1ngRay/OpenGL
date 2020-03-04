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
		//绑定不实现切线空间和法线贴图的VAOVBO
		float vertices[] = {
			// 顶点               法线                纹理坐标
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
		//绑定实现切线空间和法线贴图的VAOVBO
		float vertices_with_tangent[] = {
			//顶点                法线                纹理坐标       T
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
		//TODO:为什么有时候需要法线，有时候不用呢
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
		glm::mat4 model(1.0f);//计算并向着色器传入pvm矩阵
		model = glm::translate(model, glm::vec3(-1.0f, 0, 0));
		model = glm::scale(model, glm::vec3(0.5f));
		model = glm::rotate(model, (float)glfwGetTime() * 0.3f, glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1280.0f / 720.0f, 0.1f, 100.0f);
		withoutShader.SetMat4("model", model);
		withoutShader.SetMat4("view", view);
		withoutShader.SetMat4("projection", projection);
		withoutShader.SetVec3("viewPosition", camera.Position);//传入参数，视角位置

		glm::vec3 directLight = glm::vec3(-0.3f, 0.0f, -1.0f);
		glm::vec3 ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);
		glm::vec3 diffuseLight = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 specularLight = glm::vec3(1.0f, 1.0f, 1.0f);
		withoutShader.SetVec3("directLight", directLight);//光线方向
		withoutShader.SetVec3("ambientLight", ambientLight);//环境光参数
		withoutShader.SetVec3("diffuseLight", diffuseLight);//漫反射参数
		withoutShader.SetVec3("specularLight", specularLight);//镜面反射参数

		glActiveTexture(GL_TEXTURE0); //激活的标识为0纹理单元
		glBindTexture(GL_TEXTURE_2D, texture);
		//withoutShader.SetInt("materialTex", 0); //设置为0，与GL_TEXTURE0关联，从而使texture与materialTex关联

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normal);
		//withoutShader.SetInt("normalTex", 1);

		glBindVertexArray(withoutVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36); //TODO:为甚是36
		glBindVertexArray(0);


		//绘制在切线空间内的法线贴图
		withShader.Use();
		model = glm::mat4(1.0f);//pvm矩阵
		model = glm::translate(model, glm::vec3(1.0f, 0, 0));
		model = glm::scale(model, glm::vec3(0.5f));
		model = glm::rotate(model, (float)glfwGetTime() * 0.3f, glm::vec3(0.5f, 1.0f, 0.0f));
		withShader.SetMat4("model", model);
		withShader.SetMat4("view", view);
		withShader.SetMat4("projection", projection);
		withShader.SetVec3("viewPosition", camera.Position);
		//光线参数
		withShader.SetVec3("directLight", directLight);
		withShader.SetVec3("ambientLight", ambientLight);
		withShader.SetVec3("diffuseLight", diffuseLight);
		withShader.SetVec3("specularLight", specularLight);

		//传入正常纹理和法线贴图 
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
