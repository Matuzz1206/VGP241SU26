#pragma once
#include <string>

class Texture
{
public:
	Texture();
	Texture(const std::string& filePath);

	void Print() const;

	std::string mFilePath;
};