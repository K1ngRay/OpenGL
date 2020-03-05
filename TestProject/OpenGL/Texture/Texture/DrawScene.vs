#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal; //������;��淴�䶼��Ҫ�õ�����ƽ��ķ���
out vec3 FragPos;
out vec2 TexCoords;
out vec4 LightSpaceFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightPV; //��Դ�ռ����

void main(){
	FragPos = vec3(model * vec4(aPos,1.0));
	//���߾��󱻶���Ϊ��ģ�;������Ͻǵ�������ת�þ���
	//�ڽ��в��ȱ���������ʱ�����÷�����Ȼ��ֱƽ��
	Normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoords = aTexCoords;
	//��Դ�ռ��µ�ƬԪλ��
	LightSpaceFragPos = lightPV * vec4(FragPos,1.0); 
	//��Ļ�ռ��µ�ƬԪλ��
	gl_Position = projection * view * vec4(FragPos,1.0);//����������Ӧ�ÿ��Ի��� * model * vec4(aPos,1.0)
}