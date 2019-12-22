#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<malloc.h>
using namespace std;

const char *vertex_shader_source =
"#version 330 core\n"
"layout(location=0) in vec3 aPos;\n"
"void main(){\n"
"	gl_Position=vec4(aPos,1.0f);\n"
"}\n\0";

const char *fragment_shader_source1 =
"#version 330 core\n"
"out vec4 fragColor;\n"
"void main(){\n"
"	fragColor = vec4(1.0, 0.0, 0.0, 1.0);"
"}\n\0";

const char *fragment_shader_source2 =
"#version 330 core\n"
"out vec4 fragColor;\n"
"void main(){\n"
"	fragColor = vec4(0.0, 1.0, 0.0, 1.0);"
"}\n\0";


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	int width = 1280, height = 720;
	auto window = glfwCreateWindow(width, height, "Quad", nullptr, nullptr);
	if (window==nullptr)
	{
		cout << "Create Window Failed" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);//将窗口的上下文设置为当前线程的上下文
	//“上下文”——OpenGL是一个状态机，其状态就是上下文

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, width, height);
	
	int success;
	char info_log[512];
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader_source,NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, info_log);
		cout << "Failed to Compile Vertex Shader for " << info_log << endl;
	}

	int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragment_shader_source1, NULL);
	glCompileShader(fragmentShader1);
	glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader1, 512, NULL, info_log);
		cout << "Failed to Compile Fragment Shader 1 for "<< info_log << endl;
	}

	int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragment_shader_source2, NULL);
	glCompileShader(fragmentShader2);
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader2, 512, NULL, info_log);
		cout << "Failed to Compile Fragment Shader 1 for " << info_log << endl;
	}

	int shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);
	glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram1, 512, NULL, info_log);
		cout << "Failed to Linking Shader Program 1 for" << info_log << endl;
	}

	int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram2, 512, NULL, info_log);
		cout << "Failed to Linking Shader Program 1 for" << info_log << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);

	float firstTriangle[] = {
		// 第一个三角形
		-0.5f, -0.5f, 0.0f, //left
		0.5f, -0.5f, 0.0f, //right
		0.0f, 0.5f, 0.0f //top
	};

	float secondTriangle[] = {
		//第二个三角形
		0.5f, 0.5f, 0.0f, //left
		0.5f, -0.5f, 0.0f, //right
		0.0f, 0.5f, 0.0f //top
	};

	unsigned int VAOs[2], VBOs[2];
	GLint nrAttributes;
	glGenVertexArrays(2, VAOs);	
	glGenBuffers(2, VBOs);

	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); //第5个参数填0则是默认数据类型*维度
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);//第5个参数填0则是默认数据类型*维度
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram1);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//交换缓冲与监听事件
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	glfwTerminate();
	return 0;
}

