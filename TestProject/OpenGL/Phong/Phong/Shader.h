#pragma once

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "string"
		 
using namespace std;

class Shader
{
public:

	enum CheckType
	{
		Enum_Vertex,
		Enum_Fragment,
		Enum_Program
	};

	unsigned int shaderProgram;

	Shader(const string vertexShaderPath,const string fragmentShaderPath);
	~Shader();

	void SetVec3(const string &name,const glm::vec3 &value);
	void SetBool(const string &name, bool value);
	void SetFloat(const string &name, float value);
	void SetMat4(const string &name, const glm::mat4 &value);
	void Use();

private:
	string GetShaderFromFile(const string vertexShaderPath);
	int LinkShader(const char* vertexShaderCode, const char* fragmentShaderCode);
	int CheckCompileErrors(GLuint shader, CheckType type);
	int GetUniform(const string &name);
};

