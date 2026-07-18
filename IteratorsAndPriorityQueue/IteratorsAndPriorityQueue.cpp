#include <iostream>
#include <Array.h>
#include <Vector.h>
#include <PriorityQueue.h>

int main()
{
    std::cout << "Hello World!\n";

    Array<int, 20> arrayNumbers;
    Vector<int> vectorNumbers;
    PriorityQueue<int> pqNumbers;

    for (int i = 0; i < 20; ++i)
    {
        arrayNumbers[i] = (rand() % 100) + 1;
        int value = (rand() % 100) + 1;
        vectorNumbers.PushBack(value);
        pqNumbers.Push(value);
    }
    std::cout << "Iterate through Array\n";
    for (Array<int, 20>::Iterator it = arrayNumbers.Begin(); it != arrayNumbers.End(); ++it) {
        std::cout << *it << " ";   
    }

    std::cout << "\n\n";
    std::cout << "Iterate through Vector\n";

    for (Vector<int>::Iterator it = vectorNumbers.Begin(); it != vectorNumbers.End(); ++it) {
        std::cout << *it << " ";  
    }

    std::cout << "\n Iterate through Queue\n";

    while (!pqNumbers.Empty())
    {
        std::cout << pqNumbers.Top() << " ";
        pqNumbers.Pop();
    }
    std::cout << "\n\n";
}
