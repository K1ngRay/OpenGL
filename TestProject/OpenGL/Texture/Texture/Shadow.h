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
	
	//��ȾcubeʱҲ��Ⱦ�˵���
	void InitPlaneVAO(GLuint &vao, GLuint &vbo) {
		//�ذ�����
		float planeVertices[] = {
			//  ---- λ�� ----     ---- ���� ----    - �������� -
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

	//FBO�������洢ShadowMap(DepthMap)��
	//����������Ⱦ֡����(���������ͼ)
	//���裺1.�����Ͱ󶨣�FBO�����������2.�����������Ĺ��˷�ʽ��3.�������ӵ�֡����
	void InitFBOAndTexture(GLuint &depthMapFBO,GLuint &depthMap,int width,int height) {
		glGenFramebuffers(1, &depthMapFBO); //Ҫ�Լ�����֡���棬��ʹ��OpenGL��Ĭ�ϻ���
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glGenTextures(1, &depthMap); //����һ���������ڹ���FBO
		glBindTexture(GL_TEXTURE_2D, depthMap);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); //GL_DEPTH_COMPONENT����Ȼ���Ĵ����ʽ
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//�������Խ��
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); //��ȥ������������Ҳ�����Χ��������Χʱ����������ɫֵʹ�ñ�Ե��ɫ
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 }; //�ֶ����ñ�Ե��ɫֵ
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); //��OpenGL�ı�Ե��ɫֵ���Լ����õ���ɫֵ����

		//�������ӵ�֡������
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		//֡�����������ȫ��������ɫ����ģ�����������Ҫ��ʽ���� OpenGL ���ǲ������κ���ɫ���ݽ�����Ⱦ������ glDrawBuffer ��glReadBuffer �Ѷ��ͻ��ƻ�������Ϊ GL_NONE ���������
		glDrawBuffer(GL_NONE);//ָ��д�뻺����������Ӱ����ȡ�ģ�建������GL_NONE:��д����ɫ���������������Ƭ����ɫ�������ø���ɫ��
		glReadBuffer(GL_NONE);//ȷ����ɫ����������Դ
		glBindFramebuffer(GL_FRAMEBUFFER, 0); //�û�OpenGL��Ĭ��֡����
	}

	void Render(Shader &cubeShader,Shader &shadowMapShader,Shader &debugQuadShader, GLuint &cubeVAO,GLuint &planeVAO,GLuint &depthFBO,GLuint &depthMap, Camera &camera, mat4 &lightPV,vec3 &lightPos,
		unsigned int &diffuseMap,unsigned int &floor,int shadowW,int shadowH,float screenW,float screenH,float currentFrame) {
		
		//1.�л����趨�õ�֡���壬
		//  �����ж��㶼ת������Դ�ռ��½�����Ⱦ��
		//  ��Ⱦ��Ὣ��Ȼ�����Ƶ��������
		//  �л���Ĭ��֡���塣
		glBindFramebuffer(GL_FRAMEBUFFER, depthFBO); //����֡����
		glViewport(0, 0, shadowW, shadowH); //����Ϊ��Դ�ӿ�
		glClear(GL_DEPTH_BUFFER_BIT);
		shadowMapShader.Use(); 
		shadowMapShader.SetMat4("lightPV", lightPV); //�����ӽ�
		DrawSence(shadowMapShader, cubeVAO, planeVAO, currentFrame, diffuseMap, floor); //�γ������ͼ����������������������֡���壬���Զ�����Ȼ��Ƶ�depthMap
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// �����ɫ����Ȼ���
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

		//��������ͼ
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		DrawSence(cubeShader, cubeVAO, planeVAO, currentFrame, diffuseMap, floor);

		//��ʾ�����ͼ
		debugQuadShader.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		//RenderQuad();
	}

private:
	void DrawSence(Shader &shader, GLuint &cubeVAO, GLuint &planeVAO, float currentFrame, unsigned int textureID1, unsigned int textureID2) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID2);
		// ���ذ�
		glBindVertexArray(planeVAO);
		mat4 model = mat4(1.0f);
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID1);

		//����ֹ�ķ���
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

		//����ת�ķ���
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
		//����������Ļ���ı���
		unsigned int quadVAO = 0;
		unsigned int quadVBO;
		if (quadVAO == 0)
		{
			float quadVertices[] = {
				// ��Ļ����        // ��������
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
