//��������
//1. ��ʼ������������
//2. ���������嶥��VAOVBO�Լ���ɫ����������Ȳ���
//3. ������ѭ���������
//4. ʹ����������ɫ�������첢����pvm���󣬻���
//5. ѭ���������ͷ�VAOVBO

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "shader.h"

using namespace std;

const float vertices[] = {                  //����������,�����棬������ɫ
	-0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,0.0f,0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,0.0f,0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f,0.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,1.0f,0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,1.0f,0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,1.0f,0.0f,

	-0.5f,  0.5f,  0.5f,  0.0f,0.0f,1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,0.0f,1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,0.0f,1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,0.0f,1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,0.0f,1.0f,

	0.5f,  0.5f,  0.5f,  0.5f,0.0f,0.0f,
	0.5f,  0.5f, -0.5f,  0.5f,0.0f,0.0f,
	0.5f, -0.5f, -0.5f,  0.5f,0.0f,0.0f,
	0.5f, -0.5f, -0.5f,  0.5f,0.0f,0.0f,
	0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.0f,
	0.5f,  0.5f,  0.5f,  0.5f,0.0f,0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f,0.5f,0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,0.5f,0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,0.5f,0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,0.5f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,0.5f,0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,0.5f,0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,0.0f,0.5f,
	0.5f,  0.5f, -0.5f,  0.0f,0.0f,0.5f,
	0.5f,  0.5f,  0.5f,  0.0f,0.0f,0.5f,
	0.5f,  0.5f,  0.5f,  0.0f,0.0f,0.5f,
	-0.5f,  0.5f,  0.5f,  0.0f,0.0f,0.5f,
	-0.5f,  0.5f, -0.5f,  0.0f,0.0f,0.5f
};

//���ڲ���
int screen_width = 1280;
int screen_height = 720;
//�������
glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 10.0f);     //�����λ��
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);       //���������
glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);           //�����������
//��Ұ
float fov = 45.0f;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	auto window = glfwCreateWindow(screen_width, screen_height, "Cube", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "Failed to Create Window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to Initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, screen_width, screen_height);

	Shader shader("vertexShader.vs", "fragmentShader.fs");

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.34f, 0.57f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();

		//Transform ����任����
		glm::mat4 model(1);//���캯��������һ����λ����model���󣬾ֲ�����ת������������
		model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f)); //��Ҫ��תģ�ͣ��Ƕȣ���ת��
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glm::mat4 view(1);//view������������ת�����۲�����ϵ
		view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);
		glm::mat4 projection(1);//projection����ͶӰ����
		projection = glm::perspective(glm::radians(fov), (float)screen_width / screen_height, 0.1f, 100.0f);

		// ����ɫ���д������
		int model_location = glGetUniformLocation(shader.ID, "model");////��ȡ��ɫ����ĳ��������λ��
		glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
		int view_location = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
		int projection_location = glGetUniformLocation(shader.ID, "projection");
		glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

		//����
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}