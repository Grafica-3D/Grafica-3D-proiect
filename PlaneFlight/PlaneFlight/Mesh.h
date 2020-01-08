#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

struct Vertex 
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct TextureStruct
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indexes;
	std::vector<TextureStruct> textures;
	unsigned int VAO;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indexes, std::vector<TextureStruct> textures);
	void Draw(Shader shader);

private:
	unsigned int VBO, EBO;

	void setupMesh();
};
#endif