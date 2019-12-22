#ifndef MODEL_H
#define MODEL_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <stb/stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <iostream>
#include <vector>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
	/*  Model Data */
	std::vector<TextureStruct> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

	Model(std::string const& path, bool gamma = false);
	void Draw(Shader shader);

private:
	void loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<TextureStruct> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
#endif