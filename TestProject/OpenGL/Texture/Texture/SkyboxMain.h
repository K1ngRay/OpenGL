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
		float vertices[] = { //立方体数组
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
		float skybox_vertices[] = {   //天空盒顶点数组
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

	///已废弃不使用
	void InitCubeTexture(GLuint &texture) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		//在Texture.h中有详细介绍
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, channels; //宽，长，通道数
		stbi_set_flip_vertically_on_load(true);  //实现翻转y坐标,因为 OpenGL的纹理坐标起点在于左下角. 而图像纹理坐标的起点在于左上角.
		stbi_uc *data = stbi_load("texture/CG_Sprite.jpg", &width, &height, &channels, 0);

		if (data)
		{
			//Texture.h有介绍
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

	}

	///已废弃不使用
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
			stbi_set_flip_vertically_on_load(false);	//为什么这里就不用旋转y轴了呢，Texture.h有解释
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
		//Texture.h有解释
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void Render(Shader &cubeShader,Shader &skyboxShader,GLuint &cubeTex,GLuint &skyboxTex,GLuint &cubeVAO,GLuint &skyboxVAO,Camera &camera) {
		glActiveTexture(GL_TEXTURE0); //指定要激活的纹理单元，纹理单元的数量依赖于实现，但必须至少为8
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

		glBindVertexArray(cubeVAO);	//通过定义指针，让shader自动区分坐标点和uv
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0); //解绑

		//TODO：没看懂，估摸是因为片元着色器的xyww/w，要让w/w可以显示出来，又不想把天空盒的深度写进缓冲区
		glDepthFunc(GL_LEQUAL);//深度测试（初始值为GL_LESS）  输入的深度值小于或等于参考值，则通过
		glDepthMask(GL_FALSE);//禁止向深度缓冲区写入数据

		skyboxShader.Use();
		view = mat4(mat3(camera.GetViewMatrix()));// 去除view位移，相当于天空盒与摄像机的中心一致。因为矩阵的位移信息是放在第四列的，所以去掉第四列的位移信息就可以保持中心点一致
		skyboxShader.SetMat4("view", view);
		skyboxShader.SetMat4("projection", projection);

		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE);//允许向深度缓冲区写入数据
		glDepthFunc(GL_LESS);//深度测试  输入的深度值小于参考值，则通过

	}
};