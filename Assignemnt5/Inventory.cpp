#include "Inventory.h"
#include <iostream>

Inventory* Inventory::Get()
{
	static Inventory sInstance;
	return &sInstance;
}
void Inventory::PickupKey(const std::string& keyName, int amount)
{
	if (!mKeys.Has(keyName))
	{
		mKeys.Insert(keyName, KeyItem(keyName, 0));
	}
	mKeys[keyName].Add(amount);
}
void Inventory::UseKey(const std::string& keyName, int amount)
{
	if (mKeys.Has(keyName))
	{
		mKeys[keyName].Consume(amount);
		if (mKeys[keyName].GetCount() <= 0)
		{
			mKeys.Remove(keyName);
		}
	}
}
bool Inventory::HasKey(const std::string& keyName) const
{
	return mKeys.Has(keyName) && const_cast<Map<std::string, KeyItem>&>(mKeys)[keyName].GetCount() > 0;
}
int Inventory::GetKeyCount(const std::string& keyName) const
{
	if (mKeys.Has(keyName))
	{
		return const_cast<Map<std::string, KeyItem>&>(mKeys)[keyName].GetCount();
	}
	return 0;
}
void Inventory::ObtainKeyNames(Vector<std::string>& outNames)
{
	mKeys.ObtainKeys(outNames);
}
void Inventory::PrintAllKeys()
{
	Vector<std::string> names;
	mKeys.ObtainKeys(names);
	for (size_t i = 0; i < names.Size(); ++i)
	{
		mKeys[names[i]].Print();
	}
}