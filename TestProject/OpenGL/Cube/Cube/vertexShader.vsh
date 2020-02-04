#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 PosColor;  //layout(location = X) X为变量索引，传入的参数按照索引赋值对应的变量
out vec3 positionColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position = projection * view * model * vec4(aPos,1.0f);
	positionColor = PosColor;
}