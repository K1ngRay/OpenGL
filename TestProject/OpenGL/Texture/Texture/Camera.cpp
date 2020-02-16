#include "Camera.h"


Camera::Camera(vec3 position, vec3 worldUp, float yaw, float pitch)
	:Forward(vec3(0.0f, 0.0f, -1.0f)), Speed(defSpeed), Zoom(defZoom),Sensitivity(defSensitivity)
{
	Position = position;
	WorldUp = worldUp;
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}

Camera::~Camera()
{
}

mat4 Camera::GetViewMatrix() {
	return lookAt(Position, Position + Forward, Up);
}

void Camera::ProcessKeyboard(Camera_Movement dir, float deltaTime) {
	float velocity = Speed * deltaTime;
	switch (dir)
	{
	case Enum_FORWARD:
		Position += Forward * velocity;
		break;
	case Enum_BACKWARD:
		Position -= Forward * velocity;
		break;
	case Enum_LEFT:
		Position -= Right * velocity;
		break;
	case Enum_RIGHT:
		Position += Right * velocity;
		break;
	default:
		break;
	}
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
	xOffset *= Sensitivity;
	yOffset *= Sensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	if (constrainPitch)
	{
		if (Pitch > 90.0f)
			Pitch = 90.0f;
		if (Pitch < -90.0f)
			Pitch = -90.0f;
	}

	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset) {
	if (Zoom >= 1.0f&&Zoom <= 45.0f)
		Zoom += yOffset;
	if (Zoom < 1.0f) Zoom = 1.0f;
	if (Zoom > 45.0f) Zoom = 45.0f;
}

void Camera::UpdateCameraVectors() {
	vec3 forward;
	forward.x = cos(radians(Yaw)) * cos(radians(Pitch));
	forward.y = sin(radians(Pitch));
	forward.z = sin(radians(Yaw)) * cos(radians(Pitch));
	Forward = normalize(forward);

	Right = normalize(cross(Forward, WorldUp));
	Up = normalize(cross(Right, Forward));
}