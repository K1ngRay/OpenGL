#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const string vertexShaderPath, const string fragmentShaderPath)
{
	string vertexShaderCode = GetShaderFromFile(vertexShaderPath);
	string fragmentShaderCode = GetShaderFromFile(fragmentShaderPath);

	if (LinkShader(vertexShaderCode.c_str(), fragmentShaderCode.c_str())) return;
}


Shader::~Shader()
{
}

void Shader::SetVec3(const string &name, const glm::vec3 &value) {
	glUniform3f(GetUniform(name), value.x, value.y, value.z);
}

void Shader::SetBool(const string &name, bool value) {
	glUniform1i(GetUniform(name), (int)value);
}

void Shader::SetFloat(const string &name, float value) {
	glUniform1f(GetUniform(name), value);
}

void Shader::SetMat4(const string &name, const glm::mat4 &value) {
	glUniformMatrix4fv(GetUniform(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::Use() {
	glUseProgram(shaderProgram);
}

string Shader::GetShaderFromFile(const string vertexShaderPath)
{
	ifstream file;
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		file.open(vertexShaderPath);
		stringstream stream;
		stream << file.rdbuf();
		file.close();
		return	stream.str();
	}
	catch (const std::exception&)
	{
		cout << "Load Shader File From " << &vertexShaderPath << " Error!" << endl;
		return NULL;
	}
}

int Shader::LinkShader(const char* vertexShaderCode, const char* fragmentShaderCode) {
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);
	if (CheckCompileErrors(vertexShader, Enum_Vertex))
		return -1;

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);
	if (CheckCompileErrors(fragmentShader, Enum_Fragment))
		return -1;

	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);
	if (CheckCompileErrors(this->shaderProgram, Enum_Program))
		return -1;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return 0;
}

int Shader::CheckCompileErrors(GLuint shader, Shader::CheckType type) {
	GLint success;
	GLchar infoLog[512];
	if (type != Enum_Program)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
	}

	if (!success) {
		cout << type << " Error" << endl;
		return -1;
	}
	else return 0;
}

int Shader::GetUniform(const string &name) {
	int position = glGetUniformLocation(shaderProgram, name.c_str());
	if (position == -1)
	{
		cout << "uniform " << name << " set failed" << endl;
	}
	return position;
}