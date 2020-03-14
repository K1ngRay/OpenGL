#version 330 core
layout (location = 0) in vec3 squareVertices;

uniform vec4 xyzs; //粒子的左边和缩放
uniform vec4 color; //颜色

out vec2 UV;
out vec4 particlecolor;

uniform vec3 CameraRight_worldspace; //摄像头的右方向
uniform vec3 CameraUp_worldspace;
uniform mat4 PV; // projection-view 矩阵

void main(){
	float particleSize = xyzs.w;
	vec3 particleCenter_worldspace = xyzs.xyz;

	//采用公告板技术 让粒子始终朝向摄像头
	//根据摄像头的右方向、上方向，粒子中心位置的坐标以及粒子的大小，计算出粒子再世界空间顶点的位置
	//particleCenter_worldspace可看作以粒子坐标为原点，而Right*Up=Front，算出朝向，原点+朝向就是当前粒子坐标下的z轴方向
	vec3 vertexPosition_worldspace = 
		particleCenter_worldspace + 
		CameraRight_worldspace * squareVertices.x * particleSize +
		CameraUp_worldspace * squareVertices.y * particleSize; 

	gl_Position = PV * vec4(vertexPosition_worldspace,1.0f);

	UV = squareVertices.xy + vec2(0.5,0.5); //修正为0~1
	particlecolor = color;
}