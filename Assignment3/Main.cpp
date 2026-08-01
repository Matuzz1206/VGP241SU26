#include <iostream>
#include <string>
#include <cstdlib>
#include "KDTree.h"
#include "Vector.h"
#include "Vector3.h" 

enum PickupType
{
    PT_Invalid = 0,
    PT_Health,
    PT_WeaponAmmo,
    PT_Coins,
    PT_Upgrade,
    PT_SpecialItem,
    PT_Count
};
class Pickup
{
public:
    PickupType mType;
    std::string mName;
    Vector3 mPosition;

    Pickup()
        : mType(PT_Invalid)
        , mName("Invalid")
        , mPosition(0, 0, 0)
    {
    }

    Pickup(PickupType pickupType, const Vector3& pos)
        : mType(pickupType), mPosition(pos)
    {
        switch (pickupType)
        {
        case PT_Health:      mName = "Health"; break;
        case PT_WeaponAmmo:  mName = "WeaponAmmo"; break;
        case PT_Coins:       mName = "Coins"; break;
        case PT_Upgrade:     mName = "Upgrade"; break;
        case PT_SpecialItem: mName = "SpecialItem"; break;
        default:             mName = "Invalid"; break;
        }
    }
};
class PickupManager
{
public:
    Vector<Pickup> mPickups;
    KDTree<float, 3> mTree;

    void AddItem(PickupType pickupType, const Vector3& pos)
    {
        Pickup pickup(pickupType, pos);
        mPickups.PushBack(pickup);

        Pickup& storedPickup = mPickups[mPickups.Size() - 1];
        mTree.AddItem(&storedPickup.mPosition.x, &storedPickup);
    }
    void Build()
    {
        mTree.BuildTree();
    }
    const Pickup* GetClosestPickup(const Vector3& pos) 
    {
        const void* data = mTree.FindNearest(&pos.x);
        if (data == nullptr)
            return nullptr;
        return (const Pickup*)data;
    }
    void ObtainPickupsInRange(const Vector3& pos, float range, PickupType pickupType)
    {
        Vector<const void*> results;

        Vector3 minRange = { pos.x - range, pos.y - range, pos.z - range };
        Vector3 maxRange = { pos.x + range, pos.y + range, pos.z + range };

        struct Filter
        {
            PickupType type;
            bool operator()(const void* data)
            {
                const Pickup* p = (const Pickup*)data;
                if (type == PT_Invalid)
                    return true; 
                return p->mType == type;
            }
        } filter;

        filter.type = pickupType;

mTree.FindInRange(results, &minRange.x, &maxRange.x, filter);


        for (Vector<const void*>::Iterator it = results.Begin(); it != results.End(); ++it)
        {
            const Pickup* p = (const Pickup*)(*it);
            std::cout << "Pickup in range: " << p->mName
                << " at (" << p->mPosition.x << ", "
                << p->mPosition.y << ", "
                << p->mPosition.z << ")\n";
        }
    }
};
int main()
{
    std::srand(1234);

    PickupManager manager;

    int maxItems = 100;
    for (int i = 0; i < maxItems; ++i)
    {
        PickupType type = (PickupType)(std::rand() % PT_Count);
        Vector3 pos;
        pos.x = (float)(std::rand() % 501);
        pos.y = (float)(std::rand() % 501);
        pos.z = (float)(std::rand() % 501);

        manager.AddItem(type, pos);
    }

    manager.Build();

    Vector3 playerPos = { 250.0f, 250.0f, 250.0f };

    std::cout << "=== Player attract range 100.0f (all pickups) ===\n";
    manager.ObtainPickupsInRange(playerPos, 100.0f, PT_Invalid);

    std::cout << "\n=== Health pickups within 200.0f ===\n";
    manager.ObtainPickupsInRange(playerPos, 200.0f, PT_Health);

    std::cout << "\n=== Closest pickup to player ===\n";
    const Pickup* closest = manager.GetClosestPickup(playerPos);
    if (closest)
    {
        std::cout << "Closest pickup: " << closest->mName
            << " at (" << closest->mPosition.x << ", "
            << closest->mPosition.y << ", "
            << closest->mPosition.z << ")\n";
    }
    else
    {
        std::cout << "No pickups found.\n";
    }

    return 0;
}
