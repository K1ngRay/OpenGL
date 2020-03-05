//https://blog.csdn.net/cui6864520fei000/article/details/89949995 介绍得很详细
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
	//来自深度贴图的深度在 0 到 1 的范围，我们也打算使用 projCoords 从深度贴图中去采样，所以我们将 NDC(Normalized Device Coordinates) 坐标变换为 0 到 1 的范围：
	projCoords = projCoords * 0.5 + 0.5;

	//上两行代码是将笛卡尔坐标系的xyz转换成纹理坐标系的str，以便去深度纹理中定位采样

	float closestDepth = texture(depthMap,projCoords.xy).r; // 光的位置视野下最近的深度，纹理中的s,t,r相当于平常坐标系的x,y,z,取值r就是取值z，特就是深度
	float currentDepth = projCoords.z;// 摄像机视野下片元的当前深度
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float bias = max(0.05 * (1.0 - dot(normal,lightDir)),0.005);  //偏移量，估计是一个经验公式，法线与光线角度越小，失真越大

	//float bias = 0.005; // 阴影偏移，防止阴影失真
    //float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0; //1代表在阴影中，0代表没有在阴影中

    //PCF(percentage-closer filtering) 防锯齿
	//因为深度贴图有一个固定的解析度，多个片元对应于一个纹理像素。
	//结果就是多个片元会从深度贴图的同一个深度值进行采样，这几个片元便得到的是同一个阴影，这就会产生锯齿边。
	float shadow = 0.0;
	//textureSize返回一个给定采样器纹理的0级mipmap的vec2类型的宽和高
	//用1除以它返回一个单独纹理像素的大小，我们用以对纹理坐标进行偏移，确保每个新样本，来自不同的深度值
	vec2 texelSize = 1.0 / textureSize(depthMap,0);
	for(int x = -1; x <= 1; ++x){ //从纹理得左中右分别采样
		for(int y = -1; y <=1; ++y){ //从纹理的上中下分别采样
			
			float pcfDepth = texture(depthMap,projCoords.xy + vec2(x,y) * texelSize).r; //在原坐标下，向周围九宫格采样深度值
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /=9.0;//取了9次样，除以9取平均数

	if(projCoords.z > 1.0)
		shadow = 0.0;

	return shadow;
}

void main(){
	vec3 color = texture(diffuseTexture, TexCoords).rgb;
	vec3 normal = normalize(Normal);
	vec3 lightColor = vec3(0.4); //这个0.4是写个大概，平时是放在外面的

	vec3 ambient = 0.6 * color;//这个0.6写个大概而已
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(lightDir,normal),0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir + viewDir);//高光反射的近似计算 https://www.icourse163.org/learn/HUST-1003636001#/learn/content?type=detail&id=1211820080&cid=1214742135
	spec = pow(max(dot(normal,halfwayDir),0.0),64.0); //默认高光系数为64，数值越大，高光效果越暗
	vec3 specular = spec * lightColor;

	float shadow = ShadowCalculation(LightSpaceFragPos);
	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color; //只让漫反射和镜面反射对阴影起作用，保留环境光

	FragColor = vec4(lighting,1.0);
}