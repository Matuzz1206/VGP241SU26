#include <iostream>
#include <ctime>
#include <string>
#include <Vector.h>
#include "player.h"

std::string RandomName()
{
    static const char* names[] =
    {
        "Santiago1","Santiago2","Juan","Darren","Jacob",
        "Railey","Camilo","Daniel","Jimmy","Michael",
        "Sebastian","Hernan","Pablo","Jesus","Richard",
        "Mikel","Justin","Anuj","Mateo","Drake"
    };

    int index = std::rand() % 20;
    return names[index];
}

void PrintPlayer(const Player& p)
{
    std::cout << "Player: " << p.GetName() << "\n";
    std::cout << "  Health:  " << p.GetStat(Stats::Health) << "\n";
    std::cout << "  Attack:  " << p.GetStat(Stats::Attack) << "\n";
    std::cout << "  Defense: " << p.GetStat(Stats::Defense) << "\n";
    std::cout << "  Stamina: " << p.GetStat(Stats::Stamina) << "\n";
    std::cout << "  Speed:   " << p.GetStat(Stats::Speed) << "\n\n";
}
int FightScore(const Player& A, const Player& B)
{
    int score = A.GetStat(Stats::Health)
        - ((B.GetStat(Stats::Attack) * B.GetStat(Stats::Stamina))
            - (A.GetStat(Stats::Defense) * A.GetStat(Stats::Speed)));

    return score;
}
int main()
{
    std::srand((unsigned int)std::time(nullptr));

    Vector<Player> players;

    // Add 10 players
    for (int i = 0; i < 10; ++i)
    {
        players.PushBack(Player(RandomName()));
    }
    std::cout << "=== Initial 10 Players ===\n";
    for (std::size_t i = 0; i < players.Size(); ++i)
    {
        PrintPlayer(players[i]);
    }
    // Remove 6 players
    for (int i = 0; i < 6; ++i)
    {
        players.PopBack();
    }
    // Add until 20 players total
    while (players.Size() < 20)
    {
        players.PushBack(Player(RandomName()));
    }
    std::cout << "\n After Adding Up To 20 Players \n";
    for (std::size_t i = 0; i < players.Size(); ++i)
    {
        PrintPlayer(players[i]);
    }
    // Pick 2 random players
    int aIndex = std::rand() % players.Size();
    int bIndex = std::rand() % players.Size();
    while (bIndex == aIndex)
        bIndex = std::rand() % players.Size();

    Player& A = players[aIndex];
    Player& B = players[bIndex];

    std::cout << "\n Fight Between " << A.GetName() << " and " << B.GetName() << " ===\n";

    int scoreA = FightScore(A, B);
    int scoreB = FightScore(B, A);

    std::cout << A.GetName() << " Score: " << scoreA << "\n";
    std::cout << B.GetName() << " Score: " << scoreB << "\n";

    if (scoreA > scoreB)
    {
        std::cout << "Winner: " << A.GetName() << "\n";
    }
    else if (scoreB > scoreA)
    {
        std::cout << "Winner: " << B.GetName() << "\n";
    }
    else
    {
        std::cout << "Tie! Flipping coin...\n";
        bool coin = (std::rand() % 2) == 0;
        std::cout << "Winner: " << (coin ? A.GetName() : B.GetName()) << "\n";
    }

    return 0;
}
