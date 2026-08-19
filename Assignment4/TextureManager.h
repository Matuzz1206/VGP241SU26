#pragma once
#include <string>
#include "UnorderedMap.h"
#include "Texture.h"

class TextureManager
{
public:
	static TextureManager& GetInstance();

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;

	size_t LoadTexture(const std::string& filePath);

	Texture& GetTexture(size_t textureId);

private:
	TextureManager() = default;
	~TextureManager() = default;

	UnorderedMap<size_t, Texture> mTextures;
};