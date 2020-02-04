#pragma once
#include "Shader.h"

using namespace glm;

class Light
{
public:
	Light();
	Light(vec3 ambient, vec3 diffuse, vec3 specular);
	virtual ~Light();

	void SetAmbient(vec3 ambient); //������
	void SetDiffuse(vec3 diffuse); //������
	void SetSpecular(vec3 specular); //���淴��
	void SetActive(bool active);

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	bool active;

};

//�̳л���ǰ�����η�����������Ķ���ʱ�����Ըı����ĳ�Ա�ķ���Ȩ��
//��ԭ�������� public a;
//�̳з�ʽΪprivate
//���ⲿ�޷�ͨ���������a����Ϊ����Ȩ�޴�public�����private
class DirectLight :public Light {
public:
	DirectLight();
	DirectLight(vec3 direction);
	DirectLight(vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular);
	~DirectLight();

	void SetDirection(vec3 direction);
	void Draw(Shader shader, string name);

	vec3 direction;
};

class PointLight :public Light {
public:
	PointLight();
	PointLight(vec3 position);
	PointLight(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular);
	PointLight(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular, float constant, float linear, float quadratic);
	~PointLight();

	void SetPosition(vec3 position);
	void SetAttenuationRatio(vec3 attenuationRatio);
	void Draw(Shader shader, string name);

	vec3 position;
	float constant;
	float linear;
	float quadratic;
};

class SpotLight : public Light {
public:
	SpotLight();
	SpotLight(vec3 position, vec3 direction);
	SpotLight(vec3 position, vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular);
	SpotLight(vec3 position, vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular, float constant, float linear, float quadratic, float cut_off, float outer_cut_off);

	void SetPosition(vec3 position);
	void SetDirection(vec3 direction);
	void SetAttenuaionRatio(vec3 attenuation_ratio);
	void SetIntensityRatio(vec2 intensity_ratio);
	void Draw(Shader shader, string name);

	vec3 position;
	vec3 direction;
	float constant;
	float linear;
	float quadratic;
	float cut_off;
	float outer_cut_off;
};

