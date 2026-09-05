#pragma once

#include <random>

// Small shared-random-engine helper used by Player (stat rolls) and
// Team (random target selection / proc chances).
namespace RNG
{
    inline std::mt19937& Engine()
    {
        static std::mt19937 engine(std::random_device{}());
        return engine;
    }

    // Inclusive range [lo, hi]
    inline int RandomRange(int lo, int hi)
    {
        std::uniform_int_distribution<int> dist(lo, hi);
        return dist(Engine());
    }

    // Returns true with the given percent chance (0-100)
    inline bool RollChance(int percent)
    {
        return RandomRange(1, 100) <= percent;
    }
}