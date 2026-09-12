#include "GPS.h"
#include <cassert>

void GPS::AddCity(const std::string& name, const Vector2& pos)
{
    if (FindCityIndex(name) != -1)
    {
        return;
    }

    assert(mCities.Size() < kMaxCities);

    mCities.PushBack(City(name, pos));
    mCityGraph.AddItem(&mCities[mCities.Size() - 1]);
}

int GPS::FindCityIndex(const std::string& name) const
{
    for (std::size_t i = 0; i < mCities.Size(); ++i)
    {
        if (mCities[i].GetName() == name)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int GPS::FindCityIndex(const City& city) const
{
    return FindCityIndex(city.GetName());
}

void GPS::ConnectCities(const City& a, const City& b)
{
    int indexA = FindCityIndex(a);
    int indexB = FindCityIndex(b);

    if (indexA == -1 || indexB == -1)
    {
        return;
    }

    float weight = a.GetPosition().Distance(b.GetPosition());
    mCityGraph.AddEdge(static_cast<std::size_t>(indexA), static_cast<std::size_t>(indexB), weight);
}

float GPS::FindPath(const City& from, const City& to, Vector<const City*>& pathOutput)
{
    int start = FindCityIndex(from);
    int end = FindCityIndex(to);

    if (start == -1 || end == -1)
    {
        pathOutput.Clear();
        return -1.0f;
    }

    return mCityGraph.GetPath(start, end, pathOutput);
}