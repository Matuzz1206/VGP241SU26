#pragma once
#include <string>
#include "Vector2.h"

class House
{
public:
    House() = default;
    House(const std::string& name, const Vector2& pos)
        : mName(name), mPosition(pos)
    {
    }

    std::string mName;
    Vector2 mPosition;
};