#include "Entity.h"
#include "TextureManager.h"
#include <cstdlib>
#include <iostream>

namespace
{
	float RandomRange(float min, float max)
	{
		float t = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		return min + t * (max - min);
	}
}
Entity::Entity()
	: mTextureId(0)
	, mPosition(0.0f, 0.0f)
{
}
void Entity::Initialize(const std::string& textureFilePath)
{
	mTextureId = TextureManager::GetInstance().LoadTexture(textureFilePath);
	mPosition = Vector2(RandomRange(-200.0f, 200.0f), RandomRange(-200.0f, 200.0f));
}
void Entity::Update()
{
	mPosition = Vector2(RandomRange(-200.0f, 200.0f), RandomRange(-200.0f, 200.0f));
}
void Entity::Render() const
{
	Texture& texture = TextureManager::GetInstance().GetTexture(mTextureId);
	texture.Print();
	std::cout << "  Position: (" << mPosition.x << ", " << mPosition.y << ")" << std::endl;
}