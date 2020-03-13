#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec; //TODO:这是啥
uniform float num; //TODO:这是什么意义

struct Light{
	vec3 Position;
	vec3 Color;
};

const int NR_LIGHTS = 50;
uniform Light lights[NR_LIGHTS];
uniform vec3 viewPos;

void main(){
	//TODO:G-buffer是个什么来着
	vec3 FragColor = texture(gPosition,TexCoords).rgb;
	vec3 Normal = texture(gNormal,TexCoords).rgb;
	vec3 Diffuse = texture(gAlbedoSpec,TexCoords).rgb;
	float Specular = 1.0;

	//光照计算
	vec3 lightintg = Diffuse * 0.9;
	vec3 viewDir = normalize(viewPos - FragPos);
	for(int i = 0;i < NR_LIGHTS; i++){
		//环境光
		vec3 ambient = Diffuse * 0.01;
		//漫反射
		vec3 lightDir = normalize(light[i].Position - FragPos);
		vec3 diffuse = max(dot(Normal,lightDir),0.0) * Diffuse * lights[i].Color;
		//镜面反射
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float spec = pow(max(dot(Normal,halfwayDir),0.0),16.0);
		vec3 specular light[i].Color * spec * Specular;

		lightintg += ambient + diffuse + specular;
	}

	FragColor = vec4(lightintg/num, 1.0);
}