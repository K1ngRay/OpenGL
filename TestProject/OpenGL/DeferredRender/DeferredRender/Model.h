#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "stb/stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

class Model
{
public:
	vector<MeshTexture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;
	Model(string const &path, bool gamma = false) :gammaCorrection(gamma) {
		LoadModel(path);
	}
	void Draw(Shader shader);
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);


private:
	void LoadModel(string const &path);
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	vector<MeshTexture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeNmae);
};

#endif // !MODEL_H