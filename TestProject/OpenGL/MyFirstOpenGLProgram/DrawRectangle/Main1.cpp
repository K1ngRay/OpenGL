#define USE_EBO  1
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<malloc.h>
using namespace std;
int main2() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	int screen_width = 1280, screen_height = 720;

	auto window = glfwCreateWindow(screen_width, screen_height, "Quad", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "Failed to Create OpenGL Context" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, screen_width, screen_height);

	//生成并绑定VAO,VAO要在EBO之前绑定
	GLuint vertex_array_object;
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

#if !USE_EBO
	//采用VBO的写法
	float rectangle[] =
	{
		//第一个三角形
		0.5f,0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		//第二个三角形
		-0.5f,-0.5f,0.0f,
		0.5f,0.5f,0.0f,
		-0.5f,0.5f,0.0f,
	};
	//生成并绑定VBO
	GLuint vertex_buffer_object;
	glGenBuffers(1, &vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	//将顶点数据绑定至当前默认的缓冲中
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
#else
	//采用EBO的写法
	float rectangle[] = {
		0.5f, 0.5f, 0.0f, //右上角
		0.5f, -0.5f, 0.0f, // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f // 左上角
	};

	//索引数据
	unsigned int indices[] = { //注意索引从0开始！ 
		0, 1, 3, // 第一个三角形
		1, 2, 3 // 第二个三角形
	};

	//生成并绑定VBO
	GLuint vertex_buffer_object;
	glGenBuffers(1, &vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	//将顶点数据绑定至当前默认的缓冲中
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);


	GLuint element_buffer_object;
	glGenBuffers(1, &element_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#endif


	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//解绑VAO和VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//顶点函数
	const char *vertex_shader_source =
		"#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main(){\n"
		"	gl_Position=vec4(aPos,1.0);\n"
		"}\n\0";

	//片元函数
	const char *fragment_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"	FragColor=vec4(1.5f,1.0f,0.2f,1.0f);\n"
		"}\n\0";

	//生成并编译着色器
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	int success;
	char info_log[512];
	//检查
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		cout << "Error : Vertex Shader Complie Failed" << info_log << endl;
	}

	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	//检查
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		cout << "Error : Fragment Shader Complie Failed" << info_log << endl;
	}

	//创建程序
	int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	//检查
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		cout << "Error : Shader Program Linking Failed" << info_log << endl;
	}

	//删除着色器
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	//线框模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//开始渲染
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//使用着色器程序
		glUseProgram(shader_program);

		//绘制四边形
		glBindVertexArray(vertex_array_object);
#if !USE_EBO
		glDrawArrays(GL_TRIANGLES, 0, 6);
#else
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif
		glBindVertexArray(0);

		//交换缓冲与监听事件
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//删除VAO和VBO
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteBuffers(1, &vertex_buffer_object);
#if USE_EBO
	glDeleteBuffers(1, &element_buffer_object);
#else
#endif

	return 0;
}



