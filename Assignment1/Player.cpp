#include "Player.h"
#include <cstdlib>

Player::Player()
    : mName("Unknown")
    , mStats()
{
    Initialize();
}

Player::Player(const std::string& name)
    : mName(name)
    , mStats()
{
    Initialize();
}

void Player::Initialize()
{
    mStats[(std::size_t)Stats::Health] = 100;

    mStats[(std::size_t)Stats::Attack] = (std::rand() % 5) + 1;
    mStats[(std::size_t)Stats::Defense] = (std::rand() % 5) + 1;
    mStats[(std::size_t)Stats::Stamina] = (std::rand() % 5) + 1;
    mStats[(std::size_t)Stats::Speed] = (std::rand() % 5) + 1;
}

int Player::GetStat(Stats stat) const
{
    return mStats[(std::size_t)stat];
}

const std::string& Player::GetName() const
{
    return mName;
}
