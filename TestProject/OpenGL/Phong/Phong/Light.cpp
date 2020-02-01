#include "Light.h"

vec3 DEFAULT_AMBIENT = vec3(0.2f);
vec3 DEFAULT_DIFFUSE = vec3(0.5f);
vec3 DEFAULT_SPECULAR = vec3(1.0f);
vec3 DEFAULT_POSITION = vec3(0.0f);
vec3 DEFAULT_DIRECTION = vec3(0.0f, 0.0f, -1.0f);
vec3 DEFAULT_ATTENUATION_RATIO = vec3(1.0f, 0.09f, 0.032f);
vec2 DEFAULT_INTENSITY_RATIO = vec2(cos(radians(12.5f)), cos(radians(15.0f)));

Light::Light()
:Light(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, DEFAULT_SPECULAR)
{
}

Light::Light(vec3 ambient,vec3 diffuse,vec3 specular) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

Light::~Light()
{
}

void Light::SetAmbient(vec3 ambient) {
	this->ambient = ambient;
}

void Light::SetDiffuse(vec3 diffuse) {
	this->diffuse = diffuse;
}

void Light::SetSpecular(vec3 specular) {
	this->specular = specular;
}

void Light::SetActive(bool active) {
	this->active = active;
}

DirectLight::DirectLight() 
	:DirectLight(DEFAULT_DIRECTION)
{
}

DirectLight::DirectLight(vec3 direction) 
	:DirectLight(direction,DEFAULT_AMBIENT,DEFAULT_DIFFUSE,DEFAULT_SPECULAR)
{
}

DirectLight::DirectLight(vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular)
	: Light(ambient, diffuse, specular) 
{
	this->direction = direction;
}

DirectLight::~DirectLight() {

}

void DirectLight::SetDirection(vec3 direction) {
	this->direction = direction;
}

void DirectLight::Draw(Shader shader, string name) {
	shader.SetVec3(name + ".direction", direction);
	shader.SetVec3(name + ".ambient", ambient);
	shader.SetVec3(name + ".diffuse", diffuse);
	shader.SetVec3(name + ".specular", specular);
}

PointLight::PointLight()
	:PointLight(DEFAULT_POSITION) {
}

PointLight::PointLight(vec3 position) 
	:PointLight(position,DEFAULT_AMBIENT,DEFAULT_DIFFUSE,DEFAULT_SPECULAR)
{

}

PointLight::PointLight(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular)
	: PointLight(position, ambient, diffuse, specular, DEFAULT_ATTENUATION_RATIO.x, DEFAULT_ATTENUATION_RATIO..y, DEFAULT_ATTENUATION_RATIO.z) 
{
}

PointLight::PointLight(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular, float constant, float linear, float quadratic)
	: Light(ambient, diffuse, specular) {
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

PointLight::~PointLight() {

}

void PointLight::SetPosition(vec3 position)
{
	this->position = position;
}

void PointLight::SetAttenuationRatio(vec3 attenuationRatio) {
	this->constant = attenuationRatio.x;
	this->linear = attenuationRatio.y;
	this->quadratic = attenuationRatio.z;
}

void PointLight::Draw(Shader shader, string name) {
	shader.SetBool(name + ".active", active);
	shader.SetVec3(name + ".ambient", ambient);
	shader.SetVec3(name + ".diffuse", ambient);
	shader.SetVec3(name + ".specular", specular);
	shader.SetFloat(name + ".c", constant);
	shader.SetFloat(name + ".l", linear);
	shader.SetFloat(name + ".q", quadratic);
}

SpotLight::SpotLight()
	:SpotLight(DEFAULT_POSITION,DEFAULT_DIRECTION)
{

}

SpotLight::SpotLight(vec3 position, vec3 direction)
	: SpotLight(position, direction, DEFAULT_AMBIENT, DEFAULT_DIFFUSE, DEFAULT_SPECULAR)
{

}

SpotLight::SpotLight(vec3 position, vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular)
	: SpotLight(position,direction,ambient,diffuse,specular,
		DEFAULT_ATTENUATION_RATIO.x,DEFAULT_ATTENUATION_RATIO.y,DEFAULT_ATTENUATION_RATIO.z,
		DEFAULT_INTENSITY_RATIO.x,DEFAULT_INTENSITY_RATIO.y) {

}

SpotLight::SpotLight(vec3 position, vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular, float constant, float linear, float quadratic, float cut_off, float outer_cut_off)
	:Light(ambient, diffuse, specular) {
	this->position = position;
	this->direction = direction;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->cut_off = cut_off;
	this->outer_cut_off = outer_cut_off;
}

void SpotLight::SetPosition(vec3 position) {
	this->position = position;
}

void SpotLight::SetDirection(vec3 direction) {
	this->direction = direction;
}

void SpotLight::SetAttenuaionRatio(vec3 attenuation_ratio) {
	this->constant = attenuation_ratio.x;
	this->linear = attenuation_ratio.y;
	this->quadratic = attenuation_ratio.z;
}

void SpotLight::SetIntensityRatio(vec2 intensity_ratio) {
	this->cut_off = intensity_ratio.x;
	this->outer_cut_off = intensity_ratio.y;
}

void SpotLight::Draw(Shader shader, string name) {
	shader.SetBool(name + ".active", active);
	shader.SetVec3(name + ".ambient", ambient);
	shader.SetVec3(name + ".diffuse", diffuse);
	shader.SetVec3(name + ".specular", specular);
	shader.SetFloat(name + ".c", constant);
	shader.SetFloat(name + ".l", linear);
	shader.SetFloat(name + ".q", quadratic);
	shader.SetFloat(name + ".cut", cut_off);
	shader.SetFloat(name + ".o", outer_cut_off);
}