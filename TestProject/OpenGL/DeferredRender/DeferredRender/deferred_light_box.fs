#version 330 core
layout (location = 0) out vec4 FragColor; //TODO:��ƬԪ��ɫ���п��Ը�layout������out��

uniform vec3 lightColor;

void main(){
	FragColor = vec4(lightColor,1.0);
}