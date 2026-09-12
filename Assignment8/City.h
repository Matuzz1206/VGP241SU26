#pragma once
#include <string>
#include "Vector2.h"

class City
{
public:
    City() = default;
    City(const std::string& name, const Vector2& pos)
        : mName(name), mPosition(pos)
    {
    }

    const std::string& GetName() const { return mName; }
    const Vector2& GetPosition() const { return mPosition; }

    bool operator==(const City& rhs) const { return mName == rhs.mName; }

private:
    std::string mName;
    Vector2 mPosition;
};