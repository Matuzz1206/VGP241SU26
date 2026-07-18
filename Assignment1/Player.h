#pragma once
#include <string>
#include <Array.h>
#include "Stats.h"

class Player
{
public:
    Player();
    Player(const std::string& name);

    void Initialize();
    int GetStat(Stats stat) const;
    const std::string& GetName() const;

private:
    std::string mName;
    Array<int, (std::size_t)Stats::COUNT> mStats;
};
