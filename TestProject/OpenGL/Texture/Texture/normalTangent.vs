#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;

out VS_OUT{
	vec3 FragPos;
	vec2 TexCoords;
	mat3 TBN;
}vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position = projection * view * model * vec4(aPos,1.0);
	vs_out.FragPos = vec3(model * vec4(aPos,1.0)); //TODO:没看懂
	// Normal = mat3(model) * aNormal;
	vs_out.TexCoords = aTexCoords;
	//计算切线空间所需要的TBN矩阵
	vec3 T = normalize(vec3(model * vec4(aTangent,0.0)));
	vec3 N = normalize(vec3(model * vec4(aNormal,0.0)));
	vec3 B = normalize(cross(T,N)); //T到N还是N到T主要看T的方向，正副切线是可以互换的

	vs_out.TBN = mat3(T,B,N);
}
//使用切线空间的法线贴图