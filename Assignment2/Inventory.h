#pragma once
#include <iostream>
#include <cstdlib>
#include <Vector.h>
#include "PriorityQueue.h"
#include "Item.h"
#include "ItemCompare.h"

class Inventory
{
public:
    Vector<Item> mItems;

    void Initialize()
    {
        mItems.PushBack(Item(ItemType::SmallHealth, 10));
        mItems.PushBack(Item(ItemType::MedHealth, 25));
        mItems.PushBack(Item(ItemType::LargeHealth, 50));
        mItems.PushBack(Item(ItemType::LightningSpell, -40));
        mItems.PushBack(Item(ItemType::FireSpell, -30));
        mItems.PushBack(Item(ItemType::IceSpell, -20));
        mItems.PushBack(Item(ItemType::Grenade, -50));
        mItems.PushBack(Item(ItemType::SmokeBomb, -5));
        mItems.PushBack(Item(ItemType::Shield, 15));
        mItems.PushBack(Item(ItemType::StaminaBoost, 20));
    }
    void AddItem(ItemType itemType)
    {
        for (std::size_t i = 0; i < mItems.Size(); i++)
        {
            if (mItems[i].mType == itemType)
            {
                mItems[i].AddItem();
                return;
            }
        }
    }
    void DisplayInventory()
    {
        PriorityQueue<Item, ItemCompare> pq;

        for (auto it = mItems.Begin(); it != mItems.End(); ++it)
        {
            pq.Push(*it);
        }

        std::cout << "\n=== Inventory Sorted by Count ===\n";

        while (!pq.Empty())
        {
            const Item& top = pq.Top();
            std::cout << top.mName << " | Count: " << top.mCount << "\n";
            pq.Pop();
        }
    }
};
