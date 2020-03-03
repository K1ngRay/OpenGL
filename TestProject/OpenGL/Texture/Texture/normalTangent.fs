#version 330 core
out vec4 FragColor;

in VS_OUT{
	vec3 FragPos;
	vec2 TexCoords;
	mat3 TBN;
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
	vec3 normal = texture(normalTex,fs_in.TexCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0); //由RGB转换成切线空间的法线
	normal = normalize(fs_in.TBN * normal); //将切线空间的法线转换为世界空间的法线

	vec3 viewDir = normalize(viewPosition - fs_in.FragPos);

	vec3 dirLight = normalize(-directLight);
	float diffFactor = max(dot(normal,dirLight),0.0); 
	vec3 halfway = normalize(dirLight + viewDir); //高光反射的近似计算 https://www.icourse163.org/learn/HUST-1003636001#/learn/content?type=detail&id=1211820080&cid=1214742135
	float specFactor = pow(max(dot(halfway,normal),0.0),32); //默认高光系数为32

	vec3 color = vec3(texture(materialTex,fs_in.TexCoords));
	vec3 ambient = color * ambientLight;
	vec3 diffuse = color * diffuseLight * diffFactor;
	vec3 specular = color * specularLight * specFactor;

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result,1.0);
}
//使用切线空间的法线贴图