#include"camera.h"

using namespace glm;

Camera::Camera(vec3 position, vec3 up, float yaw, float picth)
	:Forward(vec3(0.0f, 0.0f, -1.0f))
	, Movement_Speed(SPEED)
	, Mouse_Sensiticity(SENSITIVITY)
	, Zoom(ZOOM)
{
	this->Position = position;
	this->World_Up = up;
	this->Yaw = yaw;
	this->Pitch = picth;
	UpdateCameraVectors();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch)
	:Forward(vec3(0.0f, 0.0f, -1.0f))
	, Movement_Speed(SPEED)
	, Mouse_Sensiticity(SENSITIVITY)
	, Zoom(ZOOM)
{
	this->Position = vec3(pos_x, pos_y, pos_z);
	this->World_Up = vec3(up_x, up_y, up_z);
	this->Yaw = yaw;
	this->Pitch = pitch;
	UpdateCameraVectors();
}

Camera::~Camera()
{

}

mat4 Camera::GetViewMatrix() {
	return lookAt(Position, Position + Forward, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
	float velocity = Movement_Speed * deltaTime;
	if (direction == FORWARD)
		Position += Forward * velocity;
	if (direction == BACKWARD)
		Position -= Forward * velocity;
	if (direction == RIGHT)
		Position -= Right * velocity;
	if (direction == LEFT)
		Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xOffest, float yOffest, GLboolean constrainPitch) {
	xOffest *= Mouse_Sensiticity;
	yOffest *= Mouse_Sensiticity;

	Yaw -= xOffest;
	Pitch += yOffest;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset)
{
	if (Zoom >= 1.0f&&Zoom <= 45.0f)
		Zoom += yOffset;
	if (Zoom <1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.f)
		Zoom = 45.0f;
}

void Camera::UpdateCameraVectors() {
	vec3 front;
	front.x = cos(radians(Yaw))*cos(radians(Pitch));
	front.y = sin(radians(Pitch));
	front.z = sin(radians(Yaw))*cos(radians(Pitch));
	Forward = normalize(front);
	Right = normalize(cross(Forward, World_Up)); //”“ ÷∂®‘Ú
	Up = normalize(cross(Right, Forward));
}
