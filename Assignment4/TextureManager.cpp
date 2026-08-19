#include "TextureManager.h"
#include "Global.h"

TextureManager& TextureManager::GetInstance()
{
	static TextureManager instance;
	return instance;
}

size_t TextureManager::LoadTexture(const std::string& filePath)
{
	size_t uniqueId = Global::HashFunction(filePath);

	if (!mTextures.Has(uniqueId))
	{
		mTextures.Insert(uniqueId, Texture(filePath));
	}

	return uniqueId;
}

Texture& TextureManager::GetTexture(size_t textureId)
{
	return mTextures[textureId];
}