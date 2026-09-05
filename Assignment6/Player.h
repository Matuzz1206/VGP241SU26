#pragma once

#include <string>
#include <array>

#include "Stats.h"

// 2) Player class
class Player
{
public:
    Player() = default;
    explicit Player(std::string name);

    // c. Initialize the player with default values
    //    Health = 100, Speed = 20-100, Attack = 5-20, AttackCount = 1
    void Initialize();

    // d. Returns the value for the stated stat
    int GetStat(Stats stat) const;

    // e. Update a stat
    void SetStat(Stats stat, int value);

    // f. Returns true if health > 0
    bool IsAlive() const;

    const std::string& GetName() const;

private:
    std::string mName;
    std::array<int, static_cast<size_t>(Stats::Count)> mStats{};
};