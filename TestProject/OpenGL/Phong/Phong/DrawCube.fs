#version 330 core
out vec4 FragColor;

//材质
struct Material{
	vec3 diffuse;
	vec3 specular;
	float shininess;	//镜面高光的散射/半径
}

//直射关
struct DirLight{
	bool active;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
}

//点光源
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

//聚光灯
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

//计算直射光
vec3 CalDirLight(DirLight light,vec3 normal,vec3 viewDir){
	if(!light.active){
		return vec3(0.0);
	}
	//漫反射
	vec3 lightDir = normalize(-light.direction);
	vec3 diff = max(dot(normal,lightDir),0.0);
	//镜面反射
	vec reflectDir = reflect(-lightDir);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	//漫反射的颜色
	vec3 diffuseColor = vec3(material.diffuse);
	//计算环境光，漫反射光和镜面光
	vec3 ambient = light.ambient * diffuseColor;
	vec3 diffuse = light.diffuse * diff * diffuseColor;
	vec3 specular = light.specular * spec * vec3(material.specular);
	return ambient+diffuse+specular;
}

//计算点光源
vec3 CalPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
	if(!light.active){
		return vec3(0.0);
	}
	//漫反射
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal,lightDir),0.0);
	//镜面反射
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	//距离和衰减
	float d = length(light.position - fragPos);
	float attenuation = 1.0/(light.c+light.l*d+light.q*d*d);
	//漫反射的颜色
	vec diffuseColor = vec3(material.diffuse);
	//计算环境光，漫反射光和镜面光
	vec3 ambient = light.ambient * diffuseColor;
	vec3 diffuse = light.diffuse * diff * diffuseColor;
	vec3 specular = light.specular * spec * vec3(material.specular);
	return (ambient+diffuse+specular)*attenuation;
}

//计算聚光
vec3 CalSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
	if(light.active){
		return vec3(0.0);
	}
	//漫反射
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal,lightDir),0.0);
	//镜面反射
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	//距离和衰减
	float d = length(light.position - fragPos);
	float attenuation = 1.0/(light.c+light.l*d+light.q*d*d);
	//聚光强度
	float theta = dot(lightDir,normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta-light.outerCutOff)/epsilon,0.0,1.0);
	//漫反射的颜色
	vec3 diffuseColor = vec3(material.diffuse);
	//计算环境光，漫反射光和镜面光
	vec3 ambient = light.ambient * diffuseColor;
	vec3 diffuse = light.diffuse * diff * diffuseColor;
	vec3 specular = light.specular * spec * vec3(material.specular);
	return (ambient+(diffuse+specular)*intensity)*attenuation;
}

void main(){
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	//计算直射光
	vec3 result = CalDirLight(dirLight,normal,viewDir);
	//计算点光源
	for(int i = 0;i < 6;i++){
		result += CalPointLight(pointLights,normal,viewDir);
	}
	//计算聚光灯
	result += CalSpotLight(spotLight,normal,FragPos,viewDir);
	FragColor = vec4(result,1.0);
}