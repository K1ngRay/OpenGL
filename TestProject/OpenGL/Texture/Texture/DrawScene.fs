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

//计算阴影
float ShadowCalculation(vec4 fragPosLightSpace){
	//顶点着色器输出一个裁切空间顶点位置到 gl_Position 时，OpenGL 自动进行一个透视除法，将裁切空间坐标的范围-w 到 w 转为-1 到 1，这要将 x、y、z 元素除以向量的 w 元素来实现。
	//由于裁切空间的 FragPosLightSpace 并不会通过 gl_Position 传到像素着色器里，我们必须自己做透视除法
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; 
	//来自深度贴图的深度在 0 到 1 的范围，我们也打算使用 projCoords 从深度贴图中去采样，所以我们将 NDC 坐标变换为 0 到 1 的范围：
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(depthMap,projCoords.xy).r; // 光的位置视野下最近的深度
	float currentDepth = projCoords.z;// 片元的当前深度
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float bias = max(0.05 * (1.0 - dot(normal,lightDir)),0.005);  //偏移量，估计是一个经验公式

	//float bias = 0.005; // 阴影偏移，防止阴影失真
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    //PCF(percentage-closer filtering)
	//float shadow = 0.0;
	//vec2 texelSize = 1.0 / textureSize(depthMap,0);
	//for(int x = -1; x <= 1; ++x){
	//	for(int y = -1; y <=1; ++y){
	//		float pcfDepth = texture(depthMap,projCoords.xy + vec2(x,y) * texelSize).r; //TODO:喵喵喵？
	//		shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
	//	}
	//}

	//shadow /=9.0;//TODO:喵喵喵？
	//if(projCoords.z > 1.0)
	//	shadow = 0.0;

	return shadow;
}

void main(){
	vec3 color = texture(diffuseTexture, TexCoords).rgb;
	vec3 normal = normalize(Normal);
	vec3 lightColor = vec3(0.4);

	vec3 ambient = 0.6 * color;//TODO:这个0.6是不是乱写的
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(lightDir,normal),0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal,halfwayDir),0.0),64.0);
	vec3 specular = spec * lightColor;

	float shadow = ShadowCalculation(LightSpaceFragPos);
	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

	FragColor = vec4(lighting,1.0);
}