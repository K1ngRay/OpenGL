#include "Camera.h"

Camera::Camera(vec3 position, vec3 world_up, float yaw, float pitch)
	:forward(vec3(0.0f,0.0f,1.0f)),
	mouse_sensiticity(SENSITIVITY),
	mouse_speed(SPEED),
	zoom(ZOOM)
{
	this->position = position;
	this->world_up = world_up;
	this->yaw = yaw;
	this->pitch = pitch;

	UpdateCameraVectors();
}

Camera::~Camera(){

}

mat4 Camera::GetViewMatrix() {
	return lookAt(position, position + forward, up);
}

void Camera::Move(vec3 distance) {
	position += distance;
}

void Camera::Rotate(vec3 angle) {
	//�ȵ���ƫ����
	yaw += angle.x;
	//�ٵ���������
	pitch += (flip_y ? 1 : -1)*angle.y;
	if (pitch > 90.0f) pitch = 90.0f;
	else if (pitch < -90.0f) pitch = -90.0f;

	UpdateCameraVectors();
}

void Camera::Zoom(float offset) {
	zoom += offset;
	if (zoom > 60.0f) zoom = 60.0f;
	else if (zoom < 1.0f) zoom = 1.0f;
}

void Camera::UpdateCameraVectors() {
	float rad_yaw = radians(yaw);
	float rad_pitch = radians(pitch); //ת���ɻ���

	vec3 tmpForward(1);
	tmpForward.x = cos(rad_yaw)*cos(rad_pitch);  //�����ԭ��ο���ı�ʾ���������Ƕ������������
	tmpForward.y = sin(rad_pitch);
	tmpForward.z = sin(rad_yaw)*cos(rad_pitch);

	forward = normalize(tmpForward);
	right = normalize(cross(tmpForward, world_up));
	up = normalize(cross(right, tmpForward));
}