#include <iostream>
#include "City.h"


int main()
{
    City city;

    city.AddHouse("F", Vector2(30.0f, 120.0f));
    city.AddHouse("G", Vector2(150.0f, 130.0f));
    city.AddHouse("K", Vector2(200.0f, 120.0f));
    city.AddHouse("H", Vector2(100.0f, 110.0f));
    city.AddHouse("D", Vector2(160.0f, 90.0f));
    city.AddHouse("L", Vector2(60.0f, 80.0f));
    city.AddHouse("M", Vector2(220.0f, 70.0f));
    city.AddHouse("A", Vector2(140.0f, 60.0f));
    city.AddHouse("C", Vector2(20.0f, 40.0f));
    city.AddHouse("J", Vector2(90.0f, 40.0f));
    city.AddHouse("B", Vector2(180.0f, 30.0f));

    city.ConnectAllHouses();

    const float kCostPerMeter = 10.0f;

    float primDistance = city.GetTotalRoadDistancePrim();
    float kruskalDistance = city.GetTotalRoadDistanceKruskal();

    std::cout << "=== Tabogo SIM, road planning ===\n\n";

    city.PrintMSTPrim();
    std::cout << "  Total cost: $" << (primDistance * kCostPerMeter) << "\n\n";

    city.PrintMSTKruskal();
    std::cout << "  Total cost: $" << (kruskalDistance * kCostPerMeter) << "\n\n";

    std::cout << "Cheapest road to connect all houses costs: $"
        << (primDistance * kCostPerMeter) << "\n";

    return 0;
}