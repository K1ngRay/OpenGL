#ifndef __SHADER_H__
#define __SHADER_H__ //只编译一次

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <string>
#include <glad/glad.h>
using namespace std;
class Shader
{
public:

	unsigned int ID;

	Shader(const GLchar* vertexShaderPath,const GLchar* fragmentShaderPath);
	~Shader();

	void Use();
	void SetBool(const string &shaderName, bool value) const; //表示成员函数，不能修改类的成员变量，如上面的ID
	void SetInt(const string &shaderName, int value) const;
	void SetFloat(const string &shaderName, float value) const;
	void SetVec2(const string &shaderName, const glm::vec2 &value) const;
	void SetVec2(const string &shaderName, float x, float y) const;
	void SetVec3(const string &shaderName, const glm::vec3 &value) const;
	void SetVec3(const string &shaderName, float x, float y, float z) const;
	void SetVec4(const string &shaderName, const glm::vec4 &value) const;
	void SetVec4(const string &shaderName, float x, float y, float z, float w) const;
	void SetMat2(const std::string &name, const glm::mat2 &value) const;
	void SetMat3(const std::string &name, const glm::mat3 &value) const;
	void SetMat4(const std::string &name, const glm::mat4 &value) const;

private:
	int GetShaderFromFile(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath,
		string *vertexShaderCode, string *fragmentShaderCode);
	int LinkShader(const char* vertexShaderCode, const char* fragmentShaderCode);
	int GetUniform(const string &name) const;
	void CheckCompileErrors(GLuint shader, string type);
};
#endif
