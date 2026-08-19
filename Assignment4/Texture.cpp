#include "Texture.h"
#include <iostream>

Texture::Texture()
	: mFilePath("")
{
}

Texture::Texture(const std::string& filePath)
	: mFilePath(filePath)
{
}

void Texture::Print() const
{
	std::cout << "Rendering " << mFilePath << std::endl;
}