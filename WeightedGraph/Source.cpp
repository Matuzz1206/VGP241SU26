#include <iostream>
#include <WeightedGraph.h>

int GetIndex(const Vector<std::string>& nodes, const std::string& input)
{
    for (int i = 0; i < nodes.Size(); ++i)
    {
        if (nodes[i] == input)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    std::cout << "Custom Weighted Graph\n";

    Vector<std::string> nodes;
    nodes.PushBack("A"); // 0
    nodes.PushBack("B"); // 1
    nodes.PushBack("C"); // 2
    nodes.PushBack("D"); // 3
    nodes.PushBack("E");

    WeightedGraph<std::string, int> nodeGraph;
    for (std::size_t i = 0; i < nodes.Size(); ++i)
    {
        nodeGraph.AddItem(&nodes[i]);
    }
    nodeGraph.AddEdge(0, 1, 9); // A-B 9
    nodeGraph.AddEdge(0, 2, 5); // A-C 5
    nodeGraph.AddEdge(0, 3, 2); // A-D 2
    nodeGraph.AddEdge(1, 3, 6); // B-D 6
    nodeGraph.AddEdge(1, 4, 5); // B-E 5
    nodeGraph.AddEdge(2, 3, 4); // C-D 4
    nodeGraph.AddEdge(2, 4, 5); // C-E 5
    nodeGraph.AddEdge(3, 4, 4); // D-E 4

    std::string input;
    int StartIndex = -1;
    int EndIndex = -1;
    bool done = false;

    while (!done)
    {
        system("cls");
        std::cout << "Enter Start Point (A-E): ";
        std::cin >> input;

        int startIndex = GetIndex(nodes, input);

        if (startIndex < 0)
        {
            done = input == "done";
            std::cout << "Invalid input [" << input << "]\n";
            std::cout << "Try again\n";
            system("pause");
            continue;
        }
        std::cout << "Enter End Point (A-E): ";
        std::cin >> input;

        int endIndex = GetIndex(nodes, input);

        if (endIndex < 0 || endIndex == startIndex)
        {
            done = input == "done";
            std::cout << "Invalid input [" << input << "]\n";
            std::cout << "Try again\n";
            system("pause");
            continue;
        }

        Vector<const std::string*> path;
        int totalWeight = nodeGraph.GetPath(startIndex, endIndex, path);

        if (path.Size() == 0)
        {
            std::cout << "No path was found from [" << nodes[startIndex] << "-" << nodes[endIndex] << "]\n";
            system("pause");
            continue;
        }
        std::cout << "Path from [" << nodes[startIndex] << "-" << nodes[endIndex] << "]\n";

        for (std::size_t i = 0; i < path.Size(); ++i)
        {
            std::cout << (*path[i]) << " ";
        }

        std::cout << "\n";
        std::cout << "Total Weight: " << totalWeight << "\n";
        system("pause");
    }
}