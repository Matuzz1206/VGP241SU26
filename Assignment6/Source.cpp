// Assignment 6 - Player/Team Battle Simulation with custom IntroSort
//
// Files:
//   Stats.h              - Stats enum
//   RNG.h                - shared random helpers
//   Player.h / Player.cpp - Player class
//   IntroSort.h          - templated custom IntroSort
//   Team.h / Team.cpp    - Team class
//   main.cpp             - battle driver (this file)
//
// Build:   g++ -std=c++17 -O2 -o battle main.cpp Player.cpp Team.cpp
// Run:     ./battle

#include <iostream>

#include "Team.h"

int main()
{
    Team teamA("Team A");
    Team teamB("Team B");

    teamA.Initialize(20);
    teamB.Initialize(20);

    int turn = 1;

    // >> Repeat until one team is eliminated
    while (teamA.GetRemainingPlayers() > 0 && teamB.GetRemainingPlayers() > 0)
    {
        std::cout << "\n========== Turn " << turn << " ==========\n";
        std::cout << teamA.GetName() << " remaining: " << teamA.GetRemainingPlayers()
            << " | " << teamB.GetName() << " remaining: " << teamB.GetRemainingPlayers() << "\n";

        // >> Start turn for both teams
        teamA.StartTurn();
        teamB.StartTurn();

        // > Repeat until all players have attacked this turn
        while (true)
        {
            Player* nextA = teamA.GetNextBattlingPlayer();
            Player* nextB = teamB.GetNextBattlingPlayer();

            if (!nextA && !nextB)
                break; // everyone has attacked (or is dead) this turn

            // The fastest player (across both teams) attacks the other team
            bool aGoesFirst;
            if (nextA && nextB)
                aGoesFirst = nextA->GetStat(Stats::Speed) >= nextB->GetStat(Stats::Speed);
            else
                aGoesFirst = (nextA != nullptr);

            if (aGoesFirst)
            {
                std::cout << "  " << nextA->GetName() << " (Speed " << nextA->GetStat(Stats::Speed)
                    << ") attacks " << teamB.GetName() << "!\n";
                teamB.DamagePlayer(nextA);
            }
            else
            {
                std::cout << "  " << nextB->GetName() << " (Speed " << nextB->GetStat(Stats::Speed)
                    << ") attacks " << teamA.GetName() << "!\n";
                teamA.DamagePlayer(nextB);
            }

            // > Reorder both teams after the attack
            teamA.OrderPlayers();
            teamB.OrderPlayers();

            if (teamA.GetRemainingPlayers() == 0 || teamB.GetRemainingPlayers() == 0)
                break;
        }

        ++turn;
    }

    std::cout << "\n========== BATTLE OVER ==========\n";
    int remainingA = teamA.GetRemainingPlayers();
    int remainingB = teamB.GetRemainingPlayers();

    if (remainingA > 0 && remainingB == 0)
    {
        std::cout << teamA.GetName() << " wins with " << remainingA << " player(s) remaining!\n";
    }
    else if (remainingB > 0 && remainingA == 0)
    {
        std::cout << teamB.GetName() << " wins with " << remainingB << " player(s) remaining!\n";
    }
    else
    {
        std::cout << "It's a draw!\n";
    }

    return 0;
}