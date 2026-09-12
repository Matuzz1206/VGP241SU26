#pragma once
#include "Vector.h"
#include "WeightedGraph.h"
#include "City.h"

constexpr std::size_t kMaxCities = 64;

class GPS
{
public:
    GPS()
    {
        mCities.Reserve(kMaxCities);
    }

    void AddCity(const std::string& name, const Vector2& pos);
    void ConnectCities(const City& a, const City& b);
    float FindPath(const City& from, const City& to, Vector<const City*>& pathOutput);

    int FindCityIndex(const std::string& name) const;
    int FindCityIndex(const City& city) const;

private:
    Vector<City> mCities;
    WeightedGraph<City, float> mCityGraph;
};