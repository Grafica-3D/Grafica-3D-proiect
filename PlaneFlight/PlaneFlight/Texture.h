#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <string>
#include<vector>
class Texture
{
public:
	enum TextureWrap
	{
		Repeat,
		MirroredRepeat,
		ClampToEdge,
		ClampToBorder
	};

	enum TextureFiltering
	{
		Nearest,
		Linear,
		NearestMipmapNearest,
		LinearMipmapNearest,
		NearestMipmapLinear,
		LinearMipmapLinear
	};

public:
	unsigned int id;
	Texture(const std::string& path, bool rgba);
	Texture(const std::string& path, bool rgba, TextureWrap wrap);
	Texture(const std::string& path, bool rgba, TextureWrap wrap, float borderColor[]);
	Texture(const std::string& path, bool rgba, TextureFiltering minFilter, TextureFiltering magFilter);
	Texture(const std::string& path, bool rgba, TextureWrap wrap, TextureFiltering minFilter, TextureFiltering magFilter);
	Texture(const std::string& path, bool rgba, TextureWrap wrap, float borderColor[], TextureFiltering minFilter, TextureFiltering magFilter);

};
