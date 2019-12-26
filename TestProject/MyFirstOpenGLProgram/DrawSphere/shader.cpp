#include "shader.h"
#include "fstream"
#include "sstream"
#include <iostream>

Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath) {
	string vertexShaderCode;
	string fragmentShaderCode;

	if (GetShaderFromFile(vertexShaderPath, fragmentShaderPath,&vertexShaderCode,&fragmentShaderCode))
	{
		return;
	}
	if (LinkShader(vertexShaderCode.c_str(),fragmentShaderCode.c_str()))
	{
		return;
	}
}


Shader::~Shader() {

}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetBool(const std::string &shaderName, bool value) const
{
	SetInt(shaderName, (int)value);	
}

void Shader::SetInt(const std::string &name, int value) const
{
	glUniform1i(GetUniform(name), value);
}

void Shader::SetFloat(const std::string &name, float value) const
{
	glUniform1f(GetUniform(name), value);
}

void Shader::SetVec2(const std::string &name, float x, float y) const
{
	glUniform2f(GetUniform(name), x, y);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
{
	SetVec2(name, value.x, value.y);
}

void Shader::SetVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(GetUniform(name), x, y, z);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
{
	SetVec3(name, value.x, value.y, value.z);
}

void Shader::SetVec4(const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(GetUniform(name), x, y, z, w);
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
{
	SetVec4(name, value.x, value.y, value.z, value.w);
}

void Shader::SetMat2(const std::string &name, const glm::mat2 &value) const
{
	glUniformMatrix2fv(GetUniform(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &value) const
{
	glUniformMatrix3fv(GetUniform(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &value) const
{
	glUniformMatrix4fv(GetUniform(name), 1, GL_FALSE, &value[0][0]);
}

int Shader::GetShaderFromFile(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath,
	string *vertexShaderCode, string *fragmentShaderCode) {

	ifstream vertexShaderFile;
	ifstream fragmentShaderFile;
	vertexShaderFile.exceptions(ifstream::badbit | ifstream::failbit);
	fragmentShaderFile.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		vertexShaderFile.open(vertexShaderPath);
		fragmentShaderFile.open(fragmentShaderPath);
		stringstream vertexShaderStream, fragmentShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		vertexShaderFile.close();
		fragmentShaderFile.close();
		*vertexShaderCode = vertexShaderStream.str();
		*fragmentShaderCode = fragmentShaderStream.str();
	}
	catch (const std::ifstream::failure e)
	{
		std::cout << "Load Shader File Error!" << std::endl;
		return -1;
	}
	return 0;
}

int	Shader::LinkShader(const char* vertexShaderCode, const char* fragmentShaderCode) {
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex_shader);
	CheckCompileErrors(vertex_shader, "VERTEX");

	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment_shader);
	CheckCompileErrors(fragment_shader, "FRAGMENT");

	this->ID = glCreateProgram();
	glAttachShader(ID, vertex_shader);
	glAttachShader(ID, fragment_shader);
	glLinkProgram(ID);
	CheckCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return 0;
}

int Shader::GetUniform(const string &name) const {
	int position = glGetUniformLocation(ID, name.c_str());
	if (position==-1)
	{
		std::cout << "uniform " << name << " set failed!" << std::endl;
	}
	return position;
}

void Shader::CheckCompileErrors(GLuint shader, string type) {
	GLint success;
	GLchar info_log[512];

	if (type == "PROGRAM")
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 512, NULL, info_log);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR!\n" << info_log << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, info_log);
			std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << info_log << std::endl;
		}
	}
}
