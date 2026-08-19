#pragma once
#include <cstddef>
#include <string>
#include "Vector2.h"

class Entity
{
public:
	Entity();

	void Initialize(const std::string& textureFilePath);

	void Update();

	void Render() const;

	size_t mTextureId;
	Vector2 mPosition;
};