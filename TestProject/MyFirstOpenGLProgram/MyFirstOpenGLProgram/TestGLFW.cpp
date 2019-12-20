#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

int main() {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //glfw���汾��Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //glfw�ΰ汾��Ϊ3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //ʹ�ú���ģʽ��Ҫ��ʹ��VAO

	int Major, Minor, Rev;
	glfwGetVersion(&Major, &Minor, &Rev);
	cout << Major << " " << Minor << " " << Rev << endl;

	//��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "window", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW Window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //�����ڵ�����������Ϊ��ǰ�̵߳�������
	//�������ġ�����OpenGL��һ��״̬������״̬����������

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		//����
		glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
