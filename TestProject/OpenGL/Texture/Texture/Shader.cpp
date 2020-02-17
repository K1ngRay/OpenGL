#include "Shader.h"

#include"fstream"
#include"sstream"
#include"iostream"

Shader::Shader(const char* vPath,const char* fPath)
{
	string vCode = GetShaderFromFile(vPath);
	string fCode = GetShaderFromFile(fPath);

	success = 1;
	if (!LinkShader(vCode.c_str(), fCode.c_str())) 
		success = 0;
}

Shader::~Shader()
{
}

void Shader::Use() {
	glUseProgram(this->shaderProgram);
}

void Shader::SetBool(const string &name,bool value) {
	SetInt(name, (int)value);
}

void Shader::SetInt(const string &name, int value) {
	glUniform1i(GetUniform(name), value);
}

void Shader::SetFloat(const string &name, float value) {
	glUniform1f(GetUniform(name), value);
}

void Shader::SetVec3(const string &name, vec3 &value) {
	glUniform3f(GetUniform(name), value.x, value.y, value.z);
}

void Shader::SetMat4(const string &name, mat4 &value) {
	glUniformMatrix4fv(GetUniform(name), 1, GL_FALSE, &value[0][0]); //glUniformMatrix4fv 的 "v"代表接受相应的指针类型
}

string Shader::GetShaderFromFile(const char* path) {
	ifstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		file.open(path);
		stringstream stream;
		stream << file.rdbuf();
		file.close();
		return stream.str();
	}
	catch (ifstream::failure e)
	{
		std::cout << "Load Shader File Error!" << std::endl;
		return "";
	}
}

unsigned int Shader::LinkShader(const char* vCode, const char* fCode) {
	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vCode, NULL);
	glCompileShader(vShader);
	if (!CheckError(vShader, "SHADER")) 
		return 0;

	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fCode, NULL);
	glCompileShader(fShader);
	if (!CheckError(fShader, "SHADER")) 
		return 0;

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);
	if (!CheckError(shaderProgram, "PROGRAM")) 
		return 0;

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	return 1;
}

int Shader::GetUniform(const string &name) {
	int position = glGetUniformLocation(shaderProgram, name.c_str());
	if (position == -1)
	{
		std::cout << "uniform " << name << " set failed!" << std::endl;
	}
	return position;
}

unsigned int Shader::CheckError(unsigned int shader, string type) {
	GLint success;
	GLchar infoLog[512];
	if (type == "PROGRAM")
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR!\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
	return success;
}