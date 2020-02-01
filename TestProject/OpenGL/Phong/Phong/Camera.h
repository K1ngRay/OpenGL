#pragma once

#include<glad/glad.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>

using namespace glm;

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	vec3 position;
	vec3 forward;
	vec3 up;
	vec3 right;
	vec3 world_up;

	float yaw;
	float pitch;

	float mouse_speed;
	float mouse_sensiticity;
	float zoom;
	float flip_y = false;//y轴是否反转了

	Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float picth = PITCH);;
	~Camera();

	mat4 GetViewMatrix();
	void Move(vec3 distance);
	void Rotate(vec3 angle);
	void Zoom(float offset);
private:
	void UpdateCameraVectors();
};