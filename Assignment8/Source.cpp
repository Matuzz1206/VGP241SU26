#include <iostream>
#include <iomanip>
#include "GPS.h"

namespace
{
    void PrintRoute(GPS& gps, const std::string& fromName, const std::string& toName,
        const City& from, const City& to)
    {
        Vector<const City*> path;
        float distanceKm = gps.FindPath(from, to, path);

        std::cout << "Route: " << fromName << " -> " << toName << "\n";
        std::cout << "  Path: ";
        for (std::size_t i = 0; i < path.Size(); ++i)
        {
            std::cout << path[i]->GetName();
            if (i + 1 < path.Size())
            {
                std::cout << " -> ";
            }
        }
        std::cout << "\n";

        std::cout << "  Distance: " << std::fixed << std::setprecision(2) << distanceKm << " km\n";

        constexpr float kAverageSpeedKmh = 80.0f;
        float hours = distanceKm / kAverageSpeedKmh;
        int wholeHours = static_cast<int>(hours);
        int minutes = static_cast<int>((hours - wholeHours) * 60.0f + 0.5f);

        std::cout << "  Estimated duration: " << wholeHours << "h " << minutes << "m\n\n";
    }
}

int main()
{
    GPS gps;

    gps.AddCity("Powell River", Vector2(420, 605));
    gps.AddCity("Prince George", Vector2(447, 376));
    gps.AddCity("Vancouver", Vector2(475, 635));
    gps.AddCity("Burns Lake", Vector2(375, 362));
    gps.AddCity("Abbotsford", Vector2(505, 650));
    gps.AddCity("Smithers", Vector2(330, 330));
    gps.AddCity("Penticton", Vector2(600, 615));
    gps.AddCity("Terrace", Vector2(285, 345));
    gps.AddCity("Kelowna", Vector2(603, 593));
    gps.AddCity("Prince Rupert", Vector2(227, 352));
    gps.AddCity("Kamloops", Vector2(570, 555));
    gps.AddCity("Dawson Creek", Vector2(550, 268));
    gps.AddCity("Nelson", Vector2(685, 608));
    gps.AddCity("Fort St. John", Vector2(530, 243));
    gps.AddCity("Creston", Vector2(715, 625));
    gps.AddCity("Fort Nelson", Vector2(470, 102));
    gps.AddCity("Cranbrook", Vector2(740, 598));
    gps.AddCity("Dease Lake", Vector2(250, 120));
    gps.AddCity("Revelstoke", Vector2(642, 526));
    gps.AddCity("Williams Lake", Vector2(500, 475));
    gps.AddCity("Lillooet", Vector2(512, 556));
    gps.AddCity("Quesnel", Vector2(485, 430));

    City powellRiver("Powell River", Vector2(420, 605));
    City princeGeorge("Prince George", Vector2(447, 376));
    City vancouver("Vancouver", Vector2(475, 635));
    City burnsLake("Burns Lake", Vector2(375, 362));
    City abbotsford("Abbotsford", Vector2(505, 650));
    City smithers("Smithers", Vector2(330, 330));
    City penticton("Penticton", Vector2(600, 615));
    City terrace("Terrace", Vector2(285, 345));
    City kelowna("Kelowna", Vector2(603, 593));
    City princeRupert("Prince Rupert", Vector2(227, 352));
    City kamloops("Kamloops", Vector2(570, 555));
    City dawsonCreek("Dawson Creek", Vector2(550, 268));
    City nelson("Nelson", Vector2(685, 608));
    City fortStJohn("Fort St. John", Vector2(530, 243));
    City creston("Creston", Vector2(715, 625));
    City fortNelson("Fort Nelson", Vector2(470, 102));
    City cranbrook("Cranbrook", Vector2(740, 598));
    City deaseLake("Dease Lake", Vector2(250, 120));
    City revelstoke("Revelstoke", Vector2(642, 526));
    City williamsLake("Williams Lake", Vector2(500, 475));
    City lillooet("Lillooet", Vector2(512, 556));
    City quesnel("Quesnel", Vector2(485, 430));

    gps.ConnectCities(deaseLake, fortNelson);
    gps.ConnectCities(fortNelson, fortStJohn);
    gps.ConnectCities(fortStJohn, dawsonCreek);
    gps.ConnectCities(dawsonCreek, princeGeorge);
    gps.ConnectCities(princeGeorge, burnsLake);
    gps.ConnectCities(burnsLake, smithers);
    gps.ConnectCities(smithers, terrace);
    gps.ConnectCities(terrace, deaseLake);
    gps.ConnectCities(terrace, princeRupert);
    gps.ConnectCities(princeGeorge, quesnel);
    gps.ConnectCities(quesnel, williamsLake);
    gps.ConnectCities(williamsLake, lillooet);
    gps.ConnectCities(lillooet, vancouver);
    gps.ConnectCities(lillooet, kamloops);
    gps.ConnectCities(vancouver, powellRiver);
    gps.ConnectCities(vancouver, abbotsford);
    gps.ConnectCities(vancouver, penticton);
    gps.ConnectCities(abbotsford, penticton);
    gps.ConnectCities(kamloops, revelstoke);
    gps.ConnectCities(revelstoke, cranbrook);
    gps.ConnectCities(cranbrook, creston);
    gps.ConnectCities(creston, nelson);
    gps.ConnectCities(nelson, kelowna);
    gps.ConnectCities(kamloops, penticton);
    gps.ConnectCities(penticton, kelowna);

    std::cout << "=== BC GPS Route Planner ===\n\n";

    PrintRoute(gps, "Vancouver", "Cranbrook", vancouver, cranbrook);
    PrintRoute(gps, "Prince Rupert", "Kelowna", princeRupert, kelowna);
    PrintRoute(gps, "Fort Nelson", "Creston", fortNelson, creston);

    return 0;
}