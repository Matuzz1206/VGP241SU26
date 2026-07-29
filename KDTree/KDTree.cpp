#include <iostream>
#include <string>
#include <KDtree.h>
#include <Vector2.h>
enum Type {
    IT_HEALTH,
    IT_WELLNES,
    IT_MONEY,
    IT_COUNT
};
struct Item
{
    std::string name;
    Type itemType;
    Vector2 position;
    struct Filter
    {
        Type itemType;
        bool operator()(const void* data)
        {
            const Item* item = (const Item*)data;
            return item->itemType == itemType;
        }
    };
};
int main()
{

    Vector<Item> items;
    KDTree<float, 2> itemLocations;

    int maxItems = 100;
    items.Resize(maxItems);
    for (int i = 0; i < maxItems; ++i) {
        items[i].name = "ItemName" + std::to_string(i);
        items[i].itemType = (Type)(rand() % IT_COUNT);
        switch (items[i].itemType)
        {
        case IT_HEALTH: items[i].name += "HEALTH"; break;
        case IT_WELLNES: items[i].name += "WELLNES"; break;
        case IT_MONEY: items[i].name += "MONEY"; break;
        default:
            break;
        }
        items[i].position.x = (float)(rand() & 501);
        items[i].position.y = (float)(rand() & 501);
        itemLocations.AddItem(&items[i].position.x, &items[i]);
    }

    itemLocations.BuildTree();
    Vector2 minRange = { 200.0f,200.0f };
    Vector2 maxRange = { 400.0f,400.0f };
    Item::Filter filter;
    filter.itemType = IT_HEALTH;
    Vector<const void*> itemsInRange;
    itemLocations.FindInRange(itemsInRange, &minRange.x, &maxRange.x, filter);
    for (Vector<const void*>::Iterator iter = itemsInRange.Begin(); iter != itemsInRange.End(); ++iter) {
        const Item* item = (const Item*)(*iter);
        std::cout << "Item In Range: " << item->name << " (" << item->position.x << ", " << item->position.y << ")\n";
    }
}