#version 330 core
layout (location = 0) in vec3 aPos;
layout (locaiton = 1) in vec3 aNormal;
layout (locaiton = 2) in vec3 aTexCoords;

out vec3 FragColor;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	vec4 worldPos = model * vec4(aPos, 1.0);
	FragColor = worldPos.xyz;
	TexCoords = aTexCoords;

	mat3 nomalMatrix = transpose(inverse(model));
	Normal = normalMatrix * aNormal;

	gl_Position = projection * view * worldPos;
}