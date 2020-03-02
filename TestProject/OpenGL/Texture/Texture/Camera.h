#pragma once

#include<glad/glad.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>

using namespace glm;

enum Camera_Movement {
	Enum_FORWARD,
	Enum_BACKWARD,
	Enum_LEFT,
	Enum_RIGHT
};

//默认值
const float defYaw = -90.0f; //偏航角
const float defPicth = 0.0f; //俯仰角
const float defSpeed = 2.5f; //速度
const float defSensitivity = 0.1f; //灵敏度
const float defZoom = 60.0f; //视角

class Camera
{
public:

	vec3 Position;
	vec3 Forward;
	vec3 Up;
	vec3 Right;
	vec3 WorldUp;

	float Yaw;
	float Pitch;

	float Speed;
	float Sensitivity;
	float Zoom;

	Camera(vec3 position = vec3(0.0f), vec3 worldUp = vec3(0.0f, 1.0f, 0.0f), float yaw = defYaw, float pitch = defPicth);
	~Camera();

	mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement dir, float deltaTime);
	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yOffset);

private:
	void UpdateCameraVectors();
};

