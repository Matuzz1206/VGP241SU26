#include <cstdlib>
#include <ctime>
#include <iostream>
#include <Array.h>
#include <Vector.h>

int main()
{
    std::cout << "Hello World!\n";


    Array <int, 10> myCustomArray;
    Vector <int> myVector;
    myVector.Resize(10);
    for (std::size_t i = 0; i < myVector.Size(); ++i)
    {
        std::cout << (myVector[i] += rand()) << "\n";
    }
    std::cout << "\n\n";
    myVector.PopBack();
    myVector.PopBack();
    for (std::size_t i = 0; i < myVector.Size(); ++i)
    {
        std::cout << (myVector[i]) << "\n";
    }

}
/*
int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Build an array of 10 ints
    Array<int, 10> myArray;

    // Initialize them to 0
    for (std::size_t i = 0; i < myArray.Size(); ++i)
    {
        myArray[i] = 0;
    }
    // Set values to random numbers
    for (std::size_t i = 0; i < myArray.Size(); ++i)
    {
        myArray[i] = std::rand() % 100; // random 0–99
    }
    // Create a new array of 10 ints
    Array<int, 10> newArray;
    // Make it equal to the initial array
    newArray = myArray;
    // Add 5 to each element and print
    for (std::size_t i = 0; i < newArray.Size(); ++i)
    {
        newArray[i] += 5;
        std::cout << "Value " << i << ": " << newArray[i] << std::endl;
    }

    return 0;
}
*/
