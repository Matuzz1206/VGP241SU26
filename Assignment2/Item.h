#pragma once
#include <string>
#include <iostream>
#include "ItemType.h"

class Item
{
public:
    ItemType mType;
    std::string mName;
    int mValue;
    int mCount;

    // REQUIRED DEFAULT CONSTRUCTOR (fixes your Vector errors)
    Item()
        : mType(ItemType::SmallHealth), mName("Undefined"), mValue(0), mCount(0)
    {
    }

    Item(ItemType itemType, int value)
        : mType(itemType), mValue(value), mCount(0)
    {
        switch (itemType)
        {
        case ItemType::SmallHealth:     mName = "Small Health"; break;
        case ItemType::MedHealth:       mName = "Medium Health"; break;
        case ItemType::LargeHealth:     mName = "Large Health"; break;
        case ItemType::LightningSpell:  mName = "Lightning Spell"; break;
        case ItemType::FireSpell:       mName = "Fire Spell"; break;
        case ItemType::IceSpell:        mName = "Ice Spell"; break;
        case ItemType::Grenade:         mName = "Grenade"; break;
        case ItemType::SmokeBomb:       mName = "Smoke Bomb"; break;
        case ItemType::Shield:          mName = "Shield"; break;
        case ItemType::StaminaBoost:    mName = "Stamina Boost"; break;
        }
    }

    void ConsumeItem()
    {
        if (mCount > 0)
        {
            mCount--;
            std::cout << "Consumed " << mName << " (" << mValue << ")" << "\n";
        }
        else
        {
            std::cout << mName << " has none left to consume\n";
        }
    }

    void AddItem()
    {
        mCount++;
        std::cout << "Added " << mName << " | Count: " << mCount << "\n";
    }
};
