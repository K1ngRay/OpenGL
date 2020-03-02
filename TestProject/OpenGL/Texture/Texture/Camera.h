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

//Ĭ��ֵ
const float defYaw = -90.0f; //ƫ����
const float defPicth = 0.0f; //������
const float defSpeed = 2.5f; //�ٶ�
const float defSensitivity = 0.1f; //������
const float defZoom = 60.0f; //�ӽ�

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

