#pragma once
#include <string>
#include <functional>
#include "Vector.h"
namespace Global
{
	// hash function
	inline std::size_t HashFunction(const std::string& str)
	{
		std::size_t hash = 0;
		for (size_t i = 0; i < str.size(); ++i)
		{
			hash = (~hash << i) + (std::size_t)(str[i]);
		}
		return hash;
	}
	// swap 
	template<typename T>
	void Swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}
	// bubble sort
	template<typename T, typename Compare = std::less<T>>
	void BubbleSort(Vector<T>& values, Compare sortFunc = Compare{})
	{
		std::size_t size = values.Size();
		for (size_t i = 0; i < size - 1; ++i)
		{
			for (size_t j = 0; j < size - i - 1; ++j)
			{
				if (sortFunc(values[j + 1], values[j]))
				{
					Swap(values[j + 1], values[j]);
				}
			}
		}
	}
	// Selection sort
	template<typename T, typename Compare = std::less<T>>
	void SelectionSort(Vector<T>& values, Compare sortFunc = Compare{})
	{
		std::size_t size = values.Size();
		for (size_t i = 0; i < size - 1; i++)
		{
			std::size_t minIndex = i;
			for (size_t j = i + 1; j < size; j++)
			{
				if (sortFunc(values[j], values[minIndex]))
				{
					minIndex = j;
				}
			}
			if (i != minIndex)
			{
				Swap(values[i], values[minIndex]);
			}
		}
	}
}