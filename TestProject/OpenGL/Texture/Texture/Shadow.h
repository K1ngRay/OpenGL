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

	void InitCubeVAO(GLuint &vao, GLuint &vbo) {
		// 正方体
		float cubeVertices[] = {
			//  ---- 位置 ----       ---- 法线 ----   - 纹理坐标 -
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

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		glBindVertexArray(vao);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
	
	//渲染cube时也渲染了地面
	void InitPlaneVAO(GLuint &vao, GLuint &vbo) {
		//地板数据
		float planeVertices[] = {
			//  ---- 位置 ----     ---- 法线 ----    - 纹理坐标 -
			 5.0f, -0.5f,  5.0f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
			-5.0f, -0.5f,  5.0f,  0.0f, 1.0f, 0.0f,  0.0f,  0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,

			 5.0f, -0.5f,  5.0f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,
			 5.0f, -0.5f, -5.0f,  0.0f, 1.0f, 0.0f,  1.0f,  1.0f
		};

		glGenVertexArrays(1, &vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

		glBindVertexArray(vao);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	//FBO是用来存储ShadowMap(DepthMap)的
	//设置离屏渲染帧缓冲(生成深度贴图)
	//步骤：1.创建和绑定（FBO、深度纹理）；2.设置深度纹理的过滤方式；3.将纹理附加到帧缓冲
	void InitFBOAndTexture(GLuint &depthMapFBO,GLuint &depthMap,int width,int height) {
		glGenFramebuffers(1, &depthMapFBO); //要自己定义帧缓存，不使用OpenGL的默认缓冲
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glGenTextures(1, &depthMap); //创建一张纹理，用于关联FBO
		glBindTexture(GL_TEXTURE_2D, depthMap);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); //GL_DEPTH_COMPONENT：深度缓冲的储存格式
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//解决采样越界
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); //当去采样深度纹理，且采样范围超出纹理范围时，采样的颜色值使用边缘颜色
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 }; //手动设置边缘颜色值
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); //将OpenGL的边缘颜色值跟自己设置的颜色值关联

		//将纹理附加到帧缓冲上
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		//帧缓冲对象不是完全不包含颜色缓冲的，所以我们需要显式告诉 OpenGL 我们不适用任何颜色数据进行渲染。调用 glDrawBuffer 和glReadBuffer 把读和绘制缓冲设置为 GL_NONE 来做这件事
		glDrawBuffer(GL_NONE);//指定写入缓冲区，并不影响深度、模板缓冲区。GL_NONE:不写入颜色缓冲区，如果存在片段着色器则不启用该着色器
		glReadBuffer(GL_NONE);//确定颜色缓冲区的来源
		glBindFramebuffer(GL_FRAMEBUFFER, 0); //用回OpenGL的默认帧缓冲
	}

	void Render(Shader &cubeShader,Shader &shadowMapShader,Shader &debugQuadShader, GLuint &cubeVAO,GLuint &planeVAO,GLuint &depthFBO,GLuint &depthMap, Camera &camera, mat4 &lightPV,vec3 &lightPos,
		unsigned int &diffuseMap,unsigned int &floor,int shadowW,int shadowH,float screenW,float screenH,float currentFrame) {
		
		//1.切换到设定好的帧缓冲，
		//  把所有顶点都转换到光源空间下进行渲染，
		//  渲染后会将深度缓冲绘制到深度纹理，
		//  切换成默认帧缓冲。
		glBindFramebuffer(GL_FRAMEBUFFER, depthFBO); //更换帧缓冲
		glViewport(0, 0, shadowW, shadowH); //更换为光源视口
		glClear(GL_DEPTH_BUFFER_BIT);
		shadowMapShader.Use(); 
		shadowMapShader.SetMat4("lightPV", lightPV); //输入视角
		DrawSence(shadowMapShader, cubeVAO, planeVAO, currentFrame, diffuseMap, floor); //形成深度贴图，换了这个带深度纹理附件的帧缓冲，会自动将深度绘制到depthMap
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// 清除颜色和深度缓冲
		glViewport(0, 0, screenW, screenH);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cubeShader.Use();
		cubeShader.SetVec3("viewPos", camera.Position);
		cubeShader.SetMat4("lightPV", lightPV);
		cubeShader.SetVec3("lightPos", lightPos);
		mat4 view = camera.GetViewMatrix();
		mat4 projection(1);
		projection = perspective(glm::radians(camera.Zoom), screenW / screenH, 0.1f, 100.0f);
		cubeShader.SetMat4("projection", projection);
		cubeShader.SetMat4("view", view);

		//绑定纹理贴图
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		DrawSence(cubeShader, cubeVAO, planeVAO, currentFrame, diffuseMap, floor);

		//显示深度贴图
		debugQuadShader.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		//RenderQuad();
	}

private:
	void DrawSence(Shader &shader, GLuint &cubeVAO, GLuint &planeVAO, float currentFrame, unsigned int textureID1, unsigned int textureID2) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID2);
		// 画地板
		glBindVertexArray(planeVAO);
		mat4 model = mat4(1.0f);
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID1);

		//画静止的方块
		glBindVertexArray(cubeVAO);
		model = mat4(1.0f);
		model = translate(model, vec3(0.0f, 0.3f, 1.0f));
		model = scale(model, vec3(0.3f));
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = mat4(1.0f);
		model = translate(model, vec3(1.0f, 0.0f, 1.0f));
		model = scale(model, vec3(0.3f));
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//画旋转的方块
		model = mat4(1.0f);
		model = translate(model, vec3(-1.0f, 0.6f, -1.0f));
		model = rotate(model, -currentFrame, vec3(0.0f, 0.3f, 0.5f));
		model = scale(model, vec3(0.3f));
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = mat4(1.0f);
		model = translate(model, vec3(-1.0f, 0.5f, 1.0f));
		model = rotate(model, radians(60.0f), normalize(vec3(1.0, 0.0, 1.0)));
		model = scale(model, vec3(0.4f));
		model = rotate(model, currentFrame, vec3(1.0f, 0.7f, -0.5f));
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void RenderQuad() {
		//绘制铺满屏幕的四边形
		unsigned int quadVAO = 0;
		unsigned int quadVBO;
		if (quadVAO == 0)
		{
			float quadVertices[] = {
				// 屏幕坐标        // 纹理坐标
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		}
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

	}
};
