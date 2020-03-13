#pragma once
#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};
struct MeshTexture{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<MeshTexture> textures;
	unsigned int VAO;

	Mesh();
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<MeshTexture> textures);
	void Draw(Shader shader);

private:
	unsigned int VBO, EBO;
	void setupMesh();
};

#endif // !MESH_H