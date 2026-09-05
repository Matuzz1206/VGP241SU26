#include "Player.h"
#include "RNG.h"

Player::Player(std::string name) : mName(std::move(name)) {}

void Player::Initialize()
{
    SetStat(Stats::Health, 100);
    SetStat(Stats::Speed, RNG::RandomRange(20, 100));
    SetStat(Stats::Attack, RNG::RandomRange(5, 20));
    SetStat(Stats::AttackCount, 1);
}

int Player::GetStat(Stats stat) const
{
    return mStats[static_cast<size_t>(stat)];
}

void Player::SetStat(Stats stat, int value)
{
    mStats[static_cast<size_t>(stat)] = value;
}

bool Player::IsAlive() const
{
    return GetStat(Stats::Health) > 0;
}

const std::string& Player::GetName() const
{
    return mName;
}