#include "Team.h"
#include "IntroSort.h"
#include "RNG.h"

#include <iostream>
#include <algorithm>

Team::Team(std::string name) : mName(std::move(name)) {}

void Team::Initialize(int numPlayers)
{
    mPlayers.clear();
    mPlayers.reserve(numPlayers);
    for (int i = 0; i < numPlayers; ++i)
    {
        Player p(mName + " Player " + std::to_string(i + 1));
        p.Initialize();
        mPlayers.push_back(p);
    }
    OrderPlayers();
}

Player* Team::GetNextBattlingPlayer()
{
    if (mPlayers.empty())
        return nullptr;

    Player& candidate = mPlayers.front();
    if (candidate.IsAlive() && candidate.GetStat(Stats::AttackCount) > 0)
        return &candidate;

    return nullptr; // fastest available already has effective speed 0 -> nobody left to act
}

void Team::DamagePlayer(Player* attacker)
{
    if (!attacker) return;

    Player* target = GetRandomLivingPlayer();
    if (!target)
    {
        attacker->SetStat(Stats::AttackCount, 0);
        return;
    }

    int damage = attacker->GetStat(Stats::Attack);
    int newHealth = std::max(0, target->GetStat(Stats::Health) - damage);
    target->SetStat(Stats::Health, newHealth);

    std::cout << "    " << attacker->GetName() << " hits " << target->GetName()
        << " for " << damage << " damage. ("
        << target->GetName() << " HP: " << newHealth << ")\n";

    // 25% chance the target slows down by 10 (not below 5)
    if (RNG::RollChance(25))
    {
        int slowed = std::max(5, target->GetStat(Stats::Speed) - 10);
        target->SetStat(Stats::Speed, slowed);
        std::cout << "    " << target->GetName() << " is slowed! New speed: " << slowed << "\n";
    }

    // 10% chance the attacker speeds up by 5
    if (RNG::RollChance(10))
    {
        int spedUp = attacker->GetStat(Stats::Speed) + 5;
        attacker->SetStat(Stats::Speed, spedUp);
        std::cout << "    " << attacker->GetName() << " speeds up! New speed: " << spedUp << "\n";
    }

    if (!target->IsAlive())
    {
        std::cout << "    " << target->GetName() << " has been defeated!\n";
    }

    attacker->SetStat(Stats::AttackCount, 0);
}

int Team::GetRemainingPlayers() const
{
    int count = 0;
    for (const Player& p : mPlayers)
        if (p.IsAlive())
            ++count;
    return count;
}

void Team::OrderPlayers()
{
    auto effectiveSpeed = [](const Player& p) -> int
        {
            if (!p.IsAlive() || p.GetStat(Stats::AttackCount) == 0)
                return 0;
            return p.GetStat(Stats::Speed);
        };

    IntroSort(mPlayers, [&](const Player& a, const Player& b)
        {
            return effectiveSpeed(a) > effectiveSpeed(b);
        });
}

void Team::StartTurn()
{
    for (Player& p : mPlayers)
    {
        if (p.IsAlive())
            p.SetStat(Stats::AttackCount, 1);
    }
    OrderPlayers();
}

const std::string& Team::GetName() const
{
    return mName;
}

Player* Team::GetRandomLivingPlayer()
{
    std::vector<Player*> living;
    living.reserve(mPlayers.size());
    for (Player& p : mPlayers)
        if (p.IsAlive())
            living.push_back(&p);

    if (living.empty())
        return nullptr;

    int idx = RNG::RandomRange(0, static_cast<int>(living.size()) - 1);
    return living[idx];
}