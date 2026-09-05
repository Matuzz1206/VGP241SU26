#pragma once

#include <string>
#include <vector>

#include "Player.h"

// 3) Team class
class Team
{
public:
    explicit Team(std::string name);

    void Initialize(int numPlayers);

    // d. Returns the player with the fastest speed that hasn't attacked
    Player* GetNextBattlingPlayer();

    // e. Attacker (from another team) damages a random living player on this team
    void DamagePlayer(Player* attacker);

    // f. Returns the count of players with health > 0
    int GetRemainingPlayers() const;

    // g. Sorts players by fastest speed (IntroSort). Players who already
    //    attacked this turn (or are dead) are treated as speed 0 in the
    //    comparator, without mutating their actual Speed stat.
    void OrderPlayers();

    // h. Resets AttackCount for all active players, then reorders
    void StartTurn();

    const std::string& GetName() const;

private:
    Player* GetRandomLivingPlayer();

    std::string mName;
    std::vector<Player> mPlayers;
};