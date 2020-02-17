#version 330 core
out vec4 FragColor;

//名字要与顶点着色器一样才能传过来
in VS_OUT{
	vec3 FragPos;
	vec2 TexCoords;
}fs_in;

uniform sampler2D materialTex;
uniform sampler2D normalTex;

uniform vec3 directLight;
uniform vec3 ambientLight;
uniform vec3 diffuseLight;
uniform vec3 specularLight;

uniform vec3 viewPosition;

uniform mat4 model;

void main(){
	vec3 normal = texture(normalTex,fs_in.TexCoords).rgb; //TODO:这个texture要看看参数意义
	normal = normalize(normal * 2.0 - 1.0); //转换
	vec3 viewDir = normalize(viewPosition - fs_in.FragPos);

	vec3 dirLight = normalize(-directLight);
	float diffFactor = max(dot(normal,dirLight),0.0); //TODO:这是个啥
	vec3 halfway = normalize(dirLight + viewDir);
	float specFactor = pow(max(dot(halfway,normal),0.0),32); // TODO:这是个啥

	//TODO:没看懂
	vec3 color = vec3(texture(materialTex,fs_in.TexCoords));
	vec3 ambient = color * ambientLight;
	vec3 diffuse = color * diffuseLight * diffFactor;
	vec3 specular = color * specularLight * specFactor;

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result,1.0);
}
//没有使用切线空间的法线贴图