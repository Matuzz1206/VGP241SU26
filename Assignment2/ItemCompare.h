#pragma once
#include "Item.h"

struct ItemCompare
{
    bool operator()(const Item& a, const Item& b) const
    {
        return a.mCount < b.mCount;   
    }
};
