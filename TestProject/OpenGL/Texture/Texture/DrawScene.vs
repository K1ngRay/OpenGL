#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal; //漫反射和镜面反射都需要用到物体平面的法线
out vec3 FragPos;
out vec2 TexCoords;
out vec4 LightSpaceFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightPV; //光源空间矩阵

void main(){
	FragPos = vec3(model * vec4(aPos,1.0));
	//法线矩阵被定义为「模型矩阵左上角的逆矩阵的转置矩阵」
	//在进行不等比例的缩放时，能让法线仍然垂直平面
	Normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoords = aTexCoords;
	//光源空间下的片元位置
	LightSpaceFragPos = lightPV * vec4(FragPos,1.0); 
	//屏幕空间下的片元位置
	gl_Position = projection * view * vec4(FragPos,1.0);//最后这个乘数应该可以换成 * model * vec4(aPos,1.0)
}