#version 330 core
layout (locaiton = 0) out vec3 gPosition;
layout (locaiton = 1) out vec3 gNormal;
layout (locaiton = 2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;

void main(){
	gPosition = FragPos;
	gNormal = normalize(Normal);
	gAlbedoSpec.rbg = texture(texture_diffuse1,TexCoords).rgb;
}