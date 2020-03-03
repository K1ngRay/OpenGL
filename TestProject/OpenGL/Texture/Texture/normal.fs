#version 330 core
out vec4 FragColor;

//����Ҫ�붥����ɫ��һ�����ܴ�����
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
	vec3 normal = texture(normalTex,fs_in.TexCoords).rgb; //������ȡ������ͼ����Ϣ
	normal = normalize(normal * 2.0 - 1.0); //ת��

	vec3 viewDir = normalize(viewPosition - fs_in.FragPos); //�����ӽǣ���������ָ��۲���

	vec3 dirLight = normalize(-directLight);
	float diffFactor = max(dot(normal,dirLight),0.0); //��cos���ص㣬�÷��ߺͷ����ĽǶ�Խ��ɢ���������ԽС
	vec3 halfway = normalize(dirLight + viewDir);
	float specFactor = pow(max(dot(halfway,normal),0.0),32); //Ĭ�ϸ߹�ϵ��Ϊ32����ϸ��������ͼ��shader

	vec3 color = texture(materialTex,fs_in.TexCoords).rgb; //��������ȡʵ����ͼ����ɫֵ
	vec3 ambient = color * ambientLight;
	vec3 diffuse = color * diffuseLight * diffFactor;
	vec3 specular = color * specularLight * specFactor;

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result,1.0);
}
//û��ʹ�����߿ռ�ķ�����ͼ