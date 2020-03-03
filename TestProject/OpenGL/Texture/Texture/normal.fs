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
	vec3 normal = texture(normalTex,fs_in.TexCoords).rgb; //采样，取法线贴图的信息
	normal = normalize(normal * 2.0 - 1.0); //转换

	vec3 viewDir = normalize(viewPosition - fs_in.FragPos); //计算视角，向量方向指向观察者

	vec3 dirLight = normalize(-directLight);
	float diffFactor = max(dot(normal,dirLight),0.0); //用cos的特点，让法线和反射光的角度越大，散反射的亮度越小
	vec3 halfway = normalize(dirLight + viewDir);
	float specFactor = pow(max(dot(halfway,normal),0.0),32); //默认高光系数为32，详细看法线贴图的shader

	vec3 color = texture(materialTex,fs_in.TexCoords).rgb; //采样，获取实际贴图的颜色值
	vec3 ambient = color * ambientLight;
	vec3 diffuse = color * diffuseLight * diffFactor;
	vec3 specular = color * specularLight * specFactor;

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result,1.0);
}
//没有使用切线空间的法线贴图