#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Inventory.h"

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Inventory inv;
    inv.Initialize();

    for (int i = 0; i < 100; i++)
    {
        ItemType randomType = static_cast<ItemType>(std::rand() % 10);
        inv.AddItem(randomType);
    }

    inv.DisplayInventory();

    return 0;
}
