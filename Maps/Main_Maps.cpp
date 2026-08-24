#include <iostream>
#include <Map.h>

void exercise1()
{
	std::cout << "Custom Map:\n";

	Map<int, int> myIntMap;
	for (int i = 0; i < 20; i++)
	{
		int value = rand() % 1000;
		myIntMap.Insert(i, value);
		std::cout << value << " ";

	}

	std::cout << "\n";
	std::cout << "My map at 3: " << myIntMap[3] << "\n";
	std::cout << "My value at 7: " << myIntMap[7] << "\n";

	std::cout << "Map Keys:\n";
	Vector<int> keys;
	myIntMap.ObtainKeys(keys);
	for (int i = 0; i < keys.Size(); ++i)
	{
		std::cout << keys[i] << " ";
	}

	std::cout << "\n";
	std::cout << "Remove 6:\n";
	myIntMap.Remove(6);
	keys.Clear();
	myIntMap.ObtainKeys(keys);
	for (int i = 0; i < keys.Size(); ++i)
	{
		std::cout << "Key: " << keys[i] << " Value: " << myIntMap[keys[i]] << "\n";
	}
}

struct Animal
{
	int age = 0;
	int height = 0;
	int weight = 0;
	void Print()
	{
		std::cout << "Age: " << age << " Height: " << height << " Weight: " << weight << "\n";
	}
};

int main()
{
	std::cout << "Custom Map:\n";

	Vector<std::string> animals;
	animals.PushBack("Dog");
	animals.PushBack("Cat");
	animals.PushBack("Sheep");
	animals.PushBack("Horse");
	animals.PushBack("Cow");
	animals.PushBack("Chicken");
	animals.PushBack("Snake");
	animals.PushBack("Bear");

	Map<std::string, Animal> mapAnimals;

	for (int i = 0; i < animals.Size(); ++i)
	{
		Animal newAnimal;
		newAnimal.age = (rand() % 20) + 1;
		newAnimal.height = (rand() % 7) + 1;
		newAnimal.weight = (rand() % 51) + 50;
		mapAnimals.Insert(animals[i], newAnimal);
	}
	int randAnimal = rand() % animals.Size();
	std::cout << "Details of " << animals[randAnimal] << "\n";
	mapAnimals[animals[randAnimal]].Print();

	Vector<std::string> keys;
	mapAnimals.ObtainKeys(keys);
	std::cout << "Animals in order:\n";
	for (int i = 0; i < keys.Size(); ++i)
	{
		std::cout << keys[i] << "\n";
		mapAnimals[keys[i]].Print();
		std::cout << "\n";
	}
}