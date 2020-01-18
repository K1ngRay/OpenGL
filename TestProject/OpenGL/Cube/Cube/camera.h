#ifndef __CAMERA_H__
#define __CAMERA_H__

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

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


class Camera 
{
public:
	vec3 Position;
	vec3 Forward;
	vec3 Up;
	vec3 Right;
	vec3 World_Up;

	float Yaw;					//Æ«º½½Ç
	float Pitch;				//¸©Ñö½Ç
	float Movement_Speed;
	float Mouse_Sensiticity;
	float Zoom;
	bool flip_t = false;

	Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float picth = PITCH);
	Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch);
	~Camera();

	mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPicth = true);
	void ProcessMouseScroll(float yOffset);
private:
	void UpdateCameraVectors();
};

#endif // !__CAMERA_H__
