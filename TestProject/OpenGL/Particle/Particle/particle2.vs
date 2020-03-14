#version 330 core
layout (location = 0) in vec3 squareVertices;
layout (location = 1) in vec4 xyzs; //���ӵ���ߺ�����
layout (location = 2) in vec4 color; //��ɫ

out vec2 UV;
out vec4 particlecolor;

uniform vec3 CameraRight_worldspace; //����ͷ���ҷ���
uniform vec3 CameraUp_worldspace;
uniform mat4 PV; // projection-view ����

void main(){
	float particleSize = xyzs.w;
	vec3 particleCenter_worldspace = xyzs.xyz;

	//���ù���弼�� ������ʼ�ճ�������ͷ
	//��������ͷ���ҷ����Ϸ�����������λ�õ������Լ����ӵĴ�С�����������������ռ䶥���λ��
	vec3 vertexPosition_worldspace = 
		particleCenter_worldspace + 
		CameraRight_worldspace * squareVertices.x * particleSize +
		CameraUp_worldspace * squareVertices.y * particleSize;

	gl_Position = PV * vec4(vertexPosition_worldspace,1.0f);

	UV = squareVertices.xy + vec2(0.5,0.5);
	particlecolor = color;
}