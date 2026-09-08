// MSTTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <MSTGraph.h>
#include <MSTGraphK.h>

void exercise1()
{
    std::cout << "Exercise 1\n";
    std::cout << "Test MST:\n";

    Vector<std::string> letters;
    letters.PushBack("A");
    letters.PushBack("B");
    letters.PushBack("C");
    letters.PushBack("D");
    letters.PushBack("E");

    // add to mst graph
    MSTGraph<std::string, int> mstGraph;
    for (std::size_t i = 0; i < letters.Size(); ++i)
    {
        mstGraph.AddItem(&letters[i]);
    }

    // create the graph and link together
    mstGraph.AddLink(0, 1, 9); // A-B 9
    mstGraph.AddLink(0, 2, 5); // A-C 5
    mstGraph.AddLink(0, 3, 2); // A-D 2
    mstGraph.AddLink(1, 3, 6); // B-D 6
    mstGraph.AddLink(1, 4, 5); // B-E 5
    mstGraph.AddLink(2, 3, 4); // C-D 4
    mstGraph.AddLink(2, 4, 5); // C-E 5
    mstGraph.AddLink(3, 4, 4); // D-E 4

    // mst data
    Vector<const std::string*> mst;
    Vector<const std::string*> links;
    int totalWeight = 0;
    mstGraph.ObtainMST(0, mst, links, totalWeight);
    std::cout << "MST Nodes:\n";
    for (std::size_t i = 0; i < mst.Size(); ++i)
    {
        std::cout << *mst[i] << " ";
    }
    std::cout << "\n";
    std::cout << "Links:\n";
    for (std::size_t i = 0; i < links.Size(); ++i)
    {
        if (links[i] != nullptr)
        {
            std::cout << letters[i] << "-" << *links[i] << "\n";
        }
    }

    std::cout << "Total Weight: " << totalWeight << "\n";

}
void exercise2()
{
    std::cout << "Exercise 2\n";
    std::cout << "Test MSTK:\n";

    Vector<std::string> letters;
    letters.PushBack("A");
    letters.PushBack("B");
    letters.PushBack("C");
    letters.PushBack("D");
    letters.PushBack("E");

    // add to mst graph
    MSTGraphK<std::string, int> mstGraph;
    for (std::size_t i = 0; i < letters.Size(); ++i)
    {
        mstGraph.AddItem(&letters[i]);
    }

    // create the graph and link together
    mstGraph.AddEdge(0, 1, 9); // A-B 9
    mstGraph.AddEdge(0, 2, 5); // A-C 5
    mstGraph.AddEdge(0, 3, 2); // A-D 2
    mstGraph.AddEdge(1, 3, 6); // B-D 6
    mstGraph.AddEdge(1, 4, 5); // B-E 5
    mstGraph.AddEdge(2, 3, 4); // C-D 4
    mstGraph.AddEdge(2, 4, 5); // C-E 5
    mstGraph.AddEdge(3, 4, 4); // D-E 4

    // mst data
    Vector<const std::string*> mst;
    Vector<const std::string*> links;
    int totalWeight = 0;
    mstGraph.ObtainMST(mst, links, totalWeight);
    std::cout << "MST Nodes:\n";
    for (std::size_t i = 0; i < mst.Size(); ++i)
    {
        std::cout << *mst[i] << " ";
    }
    std::cout << "\n";
    std::cout << "Links:\n";
    for (std::size_t i = 0; i < links.Size(); ++i)
    {
        if (links[i] != nullptr)
        {
            std::cout << letters[i] << "-" << *links[i] << "\n";
        }
    }

    std::cout << "Total Weight: " << totalWeight << "\n";

}
int main()
{
    std::cout << "Hello World!\n";
    exercise1();
    exercise2();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file