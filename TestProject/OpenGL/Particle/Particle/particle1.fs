#version 330 core

in vec2 UV;
in vec4 particlecolor;

out vec4 color;

uniform sampler2D myTextureSampler;
uniform bool isParticleOne;

void main(){
	vec4 pColor = particlecolor;
	if(isParticleOne)
		pColor /= 256.0;
	color = texture(myTextureSampler,UV) * pColor;
}