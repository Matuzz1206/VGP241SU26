#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Entity.h"
#include "Global.h"
#include "Vector.h"

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	Vector<Entity> myEntities;
	Entity player1;
	player1.Initialize("player_texture_1");
	myEntities.PushBack(player1);

	Entity player2;
	player2.Initialize("player_texture_2");
	myEntities.PushBack(player2);

	for (int i = 0; i < 20; ++i)
	{
		Entity enemy;
		enemy.Initialize("enemy_texture_x");
		myEntities.PushBack(enemy);
	}
	auto closestToOrigin = [](const Entity& a, const Entity& b)
		{
			const Vector2 origin(0.0f, 0.0f);
			return a.mPosition.DistanceSquared(origin) < b.mPosition.DistanceSquared(origin);
		};

	const int kNumIterations = 4;
	for (int iteration = 0; iteration < kNumIterations; ++iteration)
	{
		std::cout << "===== Iteration " << (iteration + 1) << " =====" << std::endl;

		for (size_t i = 0; i < myEntities.Size(); ++i)
		{
			myEntities[i].Update();
		}
		Global::BubbleSort(myEntities, closestToOrigin);

		for (size_t i = 0; i < myEntities.Size(); ++i)
		{
			myEntities[i].Render();
		}

		std::cout << std::endl;
	}

	return 0;
}