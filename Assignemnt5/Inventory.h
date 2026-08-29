#pragma once
#include <string>
#include "Map.h"
#include "Vector.h"
#include "KeyItem.h"

class Inventory
{
public:
	static Inventory* Get();

	void PickupKey(const std::string& keyName, int amount);
	void UseKey(const std::string& keyName, int amount);
	bool HasKey(const std::string& keyName) const;
	int GetKeyCount(const std::string& keyName) const;
	void ObtainKeyNames(Vector<std::string>& outNames);
	void PrintAllKeys();

private:
	Inventory() = default;
	~Inventory() = default;
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;

	Map<std::string, KeyItem> mKeys;
};