#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; //传不传入都无所谓，用不到
layout (location = 2) in vec2 aTexCoords;

out VS_OUT{
	vec3 FragPos;
	vec2 TexCoords;
}vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	vs_out.FragPos = vec3(model * vec4(aPos,1.0f)); //TODO：要注意这里的model传的是什么
	vs_out.TexCoords = aTexCoords;
}
//没有使用切线空间的法线贴图