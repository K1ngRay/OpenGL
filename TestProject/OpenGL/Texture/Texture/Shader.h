#pragma once

#include<glad/glad.h>
#include<glm/glm/glm.hpp>
#include<string>

using namespace std;
using namespace glm;

class Shader
{
public:

	unsigned int shaderProgram;
	unsigned int success;

	Shader(const char* vPath, const char* fPath);
	~Shader();

	void Use();
	void SetBool(const string &name,bool value) /*const*/; //�������const����ʹ�ú���ֻ�ܵ���ͬ����const��׺�ĺ���
	void SetInt(const string &name, int value);
	void SetFloat(const string &name,float value);
	void SetVec3(const string &name,vec3 &value);
	void SetMat4(const string &name,mat4 &value);

private:
	string GetShaderFromFile(const char* path);
	unsigned int LinkShader(const char* vCode,const char* fCode);
	int GetUniform(const string &name);
	unsigned int CheckError(unsigned int shader, string type);
};
