#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in ver3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;
out vec4 LightSpaceFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightPV; //TODO:����Ǹ�ɶ

void main(){
	FragPos = vec3(model * vec4(aPos,1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;//TODO:��������ɶ��ѧ�߼�
	TexCoords = aTexCoords;
	LightSpaceFragPos = lightPV * vec4(FragColor,1.0);
	gl_Position = projection * view * vec4(FragColor,1.0);//TODO:����������Ӧ�ÿ��Ի��� * model * vec4(aPos,1.0)
}