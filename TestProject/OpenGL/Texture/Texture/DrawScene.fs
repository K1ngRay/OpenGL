//https://blog.csdn.net/cui6864520fei000/article/details/89949995 ���ܵú���ϸ
#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
in vec4 LightSpaceFragPos;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform sampler2D diffuseTexture;
uniform sampler2D depthMap;

//������Ӱ
float ShadowCalculation(vec4 fragPosLightSpace){
	//������ɫ�����һ�����пռ䶥��λ�õ� gl_Position ʱ��OpenGL �Զ�����һ��͸�ӳ����������пռ�����ķ�Χ-w �� w תΪ-1 �� 1����Ҫ�� x��y��z Ԫ�س��������� w Ԫ����ʵ�֡�
	//���ڲ��пռ�� FragPosLightSpace ������ͨ�� gl_Position ����������ɫ������Ǳ����Լ���͸�ӳ���
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; 
	//���������ͼ������� 0 �� 1 �ķ�Χ������Ҳ����ʹ�� projCoords �������ͼ��ȥ�������������ǽ� NDC(Normalized Device Coordinates) ����任Ϊ 0 �� 1 �ķ�Χ��
	projCoords = projCoords * 0.5 + 0.5;

	//�����д����ǽ��ѿ�������ϵ��xyzת������������ϵ��str���Ա�ȥ��������ж�λ����

	float closestDepth = texture(depthMap,projCoords.xy).r; // ���λ����Ұ���������ȣ������е�s,t,r�൱��ƽ������ϵ��x,y,z,ȡֵr����ȡֵz���ؾ������
	float currentDepth = projCoords.z;// �������Ұ��ƬԪ�ĵ�ǰ���
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float bias = max(0.05 * (1.0 - dot(normal,lightDir)),0.005);  //ƫ������������һ�����鹫ʽ����������߽Ƕ�ԽС��ʧ��Խ��

	//float bias = 0.005; // ��Ӱƫ�ƣ���ֹ��Ӱʧ��
    //float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0; //1��������Ӱ�У�0����û������Ӱ��

    //PCF(percentage-closer filtering) �����
	//��Ϊ�����ͼ��һ���̶��Ľ����ȣ����ƬԪ��Ӧ��һ���������ء�
	//������Ƕ��ƬԪ��������ͼ��ͬһ�����ֵ���в������⼸��ƬԪ��õ�����ͬһ����Ӱ����ͻ������ݱߡ�
	float shadow = 0.0;
	//textureSize����һ�����������������0��mipmap��vec2���͵Ŀ�͸�
	//��1����������һ�������������صĴ�С���������Զ������������ƫ�ƣ�ȷ��ÿ�������������Բ�ͬ�����ֵ
	vec2 texelSize = 1.0 / textureSize(depthMap,0);
	for(int x = -1; x <= 1; ++x){ //������������ҷֱ����
		for(int y = -1; y <=1; ++y){ //������������·ֱ����
			
			float pcfDepth = texture(depthMap,projCoords.xy + vec2(x,y) * texelSize).r; //��ԭ�����£�����Χ�Ź���������ֵ
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /=9.0;//ȡ��9����������9ȡƽ����

	if(projCoords.z > 1.0)
		shadow = 0.0;

	return shadow;
}

void main(){
	vec3 color = texture(diffuseTexture, TexCoords).rgb;
	vec3 normal = normalize(Normal);
	vec3 lightColor = vec3(0.4); //���0.4��д����ţ�ƽʱ�Ƿ��������

	vec3 ambient = 0.6 * color;//���0.6д����Ŷ���
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(lightDir,normal),0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir + viewDir);//�߹ⷴ��Ľ��Ƽ��� https://www.icourse163.org/learn/HUST-1003636001#/learn/content?type=detail&id=1211820080&cid=1214742135
	spec = pow(max(dot(normal,halfwayDir),0.0),64.0); //Ĭ�ϸ߹�ϵ��Ϊ64����ֵԽ�󣬸߹�Ч��Խ��
	vec3 specular = spec * lightColor;

	float shadow = ShadowCalculation(LightSpaceFragPos);
	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color; //ֻ��������;��淴�����Ӱ�����ã�����������

	FragColor = vec4(lighting,1.0);
}