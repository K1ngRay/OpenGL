#version 330 core
out vec4 FragColor;

//����
struct Material{
	vec3 diffuse;
	vec3 specular;
	float shininess;	//����߹��ɢ��/�뾶
}

//ֱ���
struct DirLight{
	bool active;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
}

//���Դ
struct PointLight{
	bool active;
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float c;
	float l;
	float q;
}

//�۹��
struct SpotLight{
	bool active;
	vec3 position;
	vec3 direction;
	vec3 cutOff;
	vec3 outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float c;
	float l;
	float q;
}

in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[6];
uniform SpotLight spotLight;

//����ֱ���
vec3 CalDirLight(DirLight light,vec3 normal,vec3 viewDir){
	if(!light.active){
		return vec3(0.0);
	}
	//������
	vec3 lightDir = normalize(-light.direction);
	vec3 diff = max(dot(normal,lightDir),0.0);
	//���淴��
	vec reflectDir = reflect(-lightDir);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	//���������ɫ
	vec3 diffuseColor = vec3(material.diffuse);
	//���㻷���⣬�������;����
	vec3 ambient = light.ambient * diffuseColor;
	vec3 diffuse = light.diffuse * diff * diffuseColor;
	vec3 specular = light.specular * spec * vec3(material.specular);
	return ambient+diffuse+specular;
}

//������Դ
vec3 CalPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
	if(!light.active){
		return vec3(0.0);
	}
	//������
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal,lightDir),0.0);
	//���淴��
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	//�����˥��
	float d = length(light.position - fragPos);
	float attenuation = 1.0/(light.c+light.l*d+light.q*d*d);
	//���������ɫ
	vec diffuseColor = vec3(material.diffuse);
	//���㻷���⣬�������;����
	vec3 ambient = light.ambient * diffuseColor;
	vec3 diffuse = light.diffuse * diff * diffuseColor;
	vec3 specular = light.specular * spec * vec3(material.specular);
	return (ambient+diffuse+specular)*attenuation;
}

//����۹�
vec3 CalSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
	if(light.active){
		return vec3(0.0);
	}
	//������
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal,lightDir),0.0);
	//���淴��
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	//�����˥��
	float d = length(light.position - fragPos);
	float attenuation = 1.0/(light.c+light.l*d+light.q*d*d);
	//�۹�ǿ��
	float theta = dot(lightDir,normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta-light.outerCutOff)/epsilon,0.0,1.0);
	//���������ɫ
	vec3 diffuseColor = vec3(material.diffuse);
	//���㻷���⣬�������;����
	vec3 ambient = light.ambient * diffuseColor;
	vec3 diffuse = light.diffuse * diff * diffuseColor;
	vec3 specular = light.specular * spec * vec3(material.specular);
	return (ambient+(diffuse+specular)*intensity)*attenuation;
}

void main(){
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	//����ֱ���
	vec3 result = CalDirLight(dirLight,normal,viewDir);
	//������Դ
	for(int i = 0;i < 6;i++){
		result += CalPointLight(pointLights,normal,viewDir);
	}
	//����۹��
	result += CalSpotLight(spotLight,normal,FragPos,viewDir);
	FragColor = vec4(result,1.0);
}