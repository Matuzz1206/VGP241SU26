#pragma once
#include <iostream>
#include "Vector.h"
#include "House.h"
#include "MSTGraph.h"
#include "MSTGraphK.h"

class City
{
public:
    static constexpr float kMaxLinkDistance = 75.0f;

    void AddHouse(const std::string& name, const Vector2& pos)
    {
        for (std::size_t i = 0; i < mHouses.Size(); ++i)
        {
            if (mHouses[i].mName == name)
            {
                return;
            }
        }
        mHouses.PushBack(House(name, pos));
    }

    void ConnectAllHouses()
    {
        const std::size_t numHouses = mHouses.Size();

        for (std::size_t i = 0; i < numHouses; ++i)
        {
            mHousesGraph.AddItem(&mHouses[i]);
            mHouseEdgesGraph.AddItem(&mHouses[i]);
        }
        for (std::size_t i = 0; i < numHouses; ++i)
        {
            for (std::size_t j = i + 1; j < numHouses; ++j)
            {
                float distance = mHouses[i].mPosition.Distance(mHouses[j].mPosition);
                if (distance <= kMaxLinkDistance)
                {
                    mHousesGraph.AddLink(i, j, distance, true);
                    mHouseEdgesGraph.AddEdge(i, j, distance);
                }
            }
        }
    }
    float GetTotalRoadDistancePrim()
    {
        Vector<const House*> mst;
        Vector<const House*> links;
        float totalWeight = 0.0f;
        mHousesGraph.ObtainMST(0, mst, links, totalWeight);
        return totalWeight;
    }

    float GetTotalRoadDistanceKruskal()
    {
        Vector<const House*> mst;
        Vector<const House*> links;
        float totalWeight = 0.0f;
        mHouseEdgesGraph.ObtainMST(mst, links, totalWeight);
        return totalWeight;
    }
    void PrintMSTPrim()
    {
        Vector<const House*> mst;
        Vector<const House*> links;
        float totalWeight = 0.0f;
        mHousesGraph.ObtainMST(0, mst, links, totalWeight);

        std::cout << "Prim's MST road connections:\n";
        for (std::size_t i = 0; i < mHouses.Size(); ++i)
        {
            if (links[i] != nullptr)
            {
                float dist = mHouses[i].mPosition.Distance(links[i]->mPosition);
                std::cout << "  " << links[i]->mName << " -- " << mHouses[i].mName
                    << "  (" << dist << "m)\n";
            }
        }
        std::cout << "  Total road distance: " << totalWeight << "m\n";
    }
    void PrintMSTKruskal()
    {
        Vector<const House*> mst;
        Vector<const House*> links;
        float totalWeight = 0.0f;
        mHouseEdgesGraph.ObtainMST(mst, links, totalWeight);

        std::cout << "Kruskal's MST road connections:\n";
        for (std::size_t i = 0; i < mHouses.Size(); ++i)
        {
            if (links[i] != nullptr)
            {
                float dist = mHouses[i].mPosition.Distance(links[i]->mPosition);
                std::cout << "  " << links[i]->mName << " -- " << mHouses[i].mName
                    << "  (" << dist << "m)\n";
            }
        }
        std::cout << "  Total road distance: " << totalWeight << "m\n";
    }

private:
    Vector<House> mHouses;
    MSTGraph<House, float> mHousesGraph;
    MSTGraphK<House, float> mHouseEdgesGraph;
};