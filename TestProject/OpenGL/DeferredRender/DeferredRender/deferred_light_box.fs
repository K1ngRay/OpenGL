#version 330 core
layout (location = 0) out vec4 FragColor; //TODO:在片元着色器中可以搞layout？还是out的

uniform vec3 lightColor;

void main(){
	FragColor = vec4(lightColor,1.0);
}