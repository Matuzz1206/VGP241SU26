#include <iostream>
#include <string>
#include "Vector.h"
#include "Inventory.h"

int main()
{
	Vector<std::string> keyNames;
	keyNames.PushBack("BronzeKey");
	keyNames.PushBack("SilverKey");
	keyNames.PushBack("GoldKey");
	keyNames.PushBack("IronKey");
	keyNames.PushBack("CopperKey");
	keyNames.PushBack("RustyKey");
	keyNames.PushBack("CrystalKey");
	keyNames.PushBack("ShadowKey");
	keyNames.PushBack("SkeletonKey");
	keyNames.PushBack("EmberKey");
	keyNames.PushBack("FrostKey");
	keyNames.PushBack("VineKey");
	keyNames.PushBack("BoneKey");
	keyNames.PushBack("StormKey");
	keyNames.PushBack("MoonKey");
	keyNames.PushBack("SunKey");
	keyNames.PushBack("RuneKey");
	keyNames.PushBack("ObsidianKey");
	keyNames.PushBack("PearlKey");
	keyNames.PushBack("JadeKey");

	Inventory* inventory = Inventory::Get();

	for (int i = 0; i < 100; ++i)
	{
		int index = rand() % keyNames.Size();
		inventory->PickupKey(keyNames[index], 1);
	}
	std::cout << "=== Starting Inventory ===" << std::endl;
	inventory->PrintAllKeys();
	std::cout << std::endl;

	int doorsUnlocked = 0;
	int failedAttempts = 0;

	bool playing = true;
	while (playing)
	{
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "1. Open a door" << std::endl;
		std::cout << "2. Obtain a key" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cout << "> ";

		int choice = 0;
		std::cin >> choice;

		if (choice == 1)
		{
			int index = rand() % keyNames.Size();
			const std::string& neededKey = keyNames[index];
			std::cout << "You arrive at a door and need a " << neededKey << std::endl;

			if (inventory->HasKey(neededKey))
			{
				std::cout << "You have the " << neededKey << " and have unlocked the door" << std::endl;
				inventory->UseKey(neededKey, 1);
				++doorsUnlocked;
			}
			else
			{
				std::cout << "You do not have the " << neededKey << ", the door will remain locked" << std::endl;
				++failedAttempts;
			}
		}
		else if (choice == 2)
		{
			int index = rand() % keyNames.Size();
			const std::string& pickedKey = keyNames[index];
			inventory->PickupKey(pickedKey, 1);
			std::cout << "You picked up a " << pickedKey
				<< ", total count: " << inventory->GetKeyCount(pickedKey) << std::endl;
		}
		else if (choice == 3)
		{
			playing = false;
		}
		else
		{
			std::cout << "Invalid choice, try again." << std::endl;
		}

		std::cout << std::endl;
	}
	std::cout << "=== Final Inventory ===" << std::endl;
	inventory->PrintAllKeys();
	std::cout << std::endl;
	std::cout << "Doors unlocked: " << doorsUnlocked << std::endl;
	std::cout << "Failed unlock attempts: " << failedAttempts << std::endl;

	return 0;
}