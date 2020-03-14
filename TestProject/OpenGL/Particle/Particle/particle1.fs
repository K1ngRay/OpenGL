#version 330 core

in vec2 UV;
in vec4 particlecolor;

out vec4 color;

uniform sampler2D myTextureSampler;

void main(){
	vec4 pColor = particlecolor;
	pColor.xyz /= 256.0;
	color = texture(myTextureSampler,UV) * pColor;
}