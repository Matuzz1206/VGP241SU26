#pragma once

#ifndef __GLOBAL_HEADER__
#define __GLOBAL_HEADER__



#include <string>
#include <functional>
#include "Vector.h"
#include <cmath>

namespace Global {
	//hash function
	inline std::size_t HashFunction(const std::string& str) {
		std::size_t hash = 0;
		for (size_t i = 0; i < str.size(); i++)
		{
			hash = (~hash << i) + (std::size_t)(str[i]);
		}
		return hash;
	}

	template<typename T>
	inline void Swap(T& a, T& b) {
		T tmp = a;
		a = b;
		b = tmp;
	}

	//bubble sort
	template<typename T, typename Compare = std::less<T>>
	inline void BubbleSort(Vector<T>& values, Compare sortFunc = Compare{}) {
		std::size_t size = values.Size();
		for (size_t i = 0; i < size - 1; i++) {
			for (size_t j = 0; j < size - i - 1; j++)
			{
				if (sortFunc(values[j + 1], values[j])) {
					Swap(values[j + 1], values[j]);
				}
			}
		}
	}
	//selection sort
	template<typename T, typename Compare = std::less<T>>
	inline void SelectionSort(Vector<T>& values, Compare sortFunc = Compare{}) {
		std::size_t size = values.Size();
		for (size_t i = 0; i < size - 1; i++) {
			std::size_t minIndex = i;
			for (size_t j = i + 1; j < size; j++)
			{
				if (sortFunc(values[j], values[minIndex])) {
					minIndex = j;
				}
			}
			if (i != minIndex) {
				Swap(values[i], values[minIndex]);
			}
		}

	}
	template<typename T, typename Compare = std::less<T>>
	inline void InsertionSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare{}) {
		if (begin == end) {
			return;
		}

		for (ContainerIterator<T> iter = begin + 1; iter != end; ++iter) {
			T key = *iter;
			ContainerIterator<T> j = iter;
			while (j > begin) {
				if (comp(key, *(j - 1))) {
					*j = *(j - 1);
					--j;
				}
				else {
					break;
				}
			}
			*j = key;
		}
	}
	//MergeSort
	namespace MergeSortHelpers
	{
		template<typename T, typename Compare>
		void Merge(ContainerIterator<T> left, ContainerIterator<T> mid, ContainerIterator<T> right, Compare comp)
		{
			Vector<T> temp;
			temp.Reserve(right - left);
			ContainerIterator<T> tempLeft = left;
			ContainerIterator<T> tempRight = mid;
			while (tempLeft != mid && tempRight != right)
			{
				if (comp(*tempLeft, *tempRight))
				{
					temp.PushBack(*tempLeft);
					++tempLeft;
				}
				else
				{
					temp.PushBack(*tempRight);
					++tempRight;
				}
			}
			while (tempLeft != mid)
			{
				temp.PushBack(*tempLeft);
				++tempLeft;
			}
			while (tempRight != right)
			{
				temp.PushBack(*tempRight);
				++tempRight;
			}
			for (std::size_t i = 0; i < temp.Size(); i++)
			{
				*(left + i) = temp[i];
			}

		}
	}

	template<typename T, typename Compare = std::less<T>>
	inline void MergeSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare{})
	{

		std::size_t size = end - begin;
		if (size > 1) {
			std::size_t half = size / 2;
			ContainerIterator<T> mid = begin + half;
			MergeSort(begin, mid, comp);
			MergeSort(mid, end, comp);

			MergeSortHelpers::Merge(begin, mid, end, comp);
		}
	}

	//quick sort
	namespace QuickSortHelpers
	{
		template<typename T, typename Compare>
		ContainerIterator<T> Partition(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp)
		{
			ContainerIterator<T> pivot = end - 1;
			ContainerIterator<T> i = begin;
			for (ContainerIterator<T> j = begin; j != pivot; ++j)
			{
				if (comp(*j, *pivot))
				{
					Swap(*i, *j);
					++i;
				}
			}
			Swap(*i, *pivot);
			return i;
		}
	}
	template<typename T, typename Compare = std::less<T>>
	inline void QuickSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare{})
	{
		if ((end - begin) > 1) {
			ContainerIterator<T> p = QuickSortHelpers::Partition(begin, end, comp);
			QuickSort(begin, p, comp);
			QuickSort(p + 1, end, comp);
		}
	}
	//bucket Sort
	template<typename T, typename Compare = std::less<T>>
	inline void BucketSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare{}) {
		ContainerIterator<T> maxValue = begin;
		for (ContainerIterator<T> iter = begin + 1; iter != end; ++iter)
		{
			if (*maxValue < *iter)
			{
				maxValue = iter;
			}
		}
		std::size_t size = (end - begin);
		Vector<Vector<T>> buckets;
		buckets.Resize(size);
		for (ContainerIterator<T> iter = begin; iter != end; ++iter)
		{
			std::size_t bucketIndex = ((size - 1) * (*iter)) / (*maxValue);
			buckets[bucketIndex].PushBack(*iter);
		}
		for (std::size_t i = 0; i < size; ++i)
		{
			InsertionSort(buckets[i].begin(), buckets[i].end());
		}
		ContainerIterator<T> iter = begin;
		for (std::size_t i = 0; i < size; ++i)
		{
			for (std::size_t j = 0; j < buckets[i].Size(); ++j)
			{
				(*iter) = buckets[i][j];
				++iter;
			}
		}

	}
	namespace HeapSortHelpers
	{
		template<typename T, typename Compare>
		void Heapify(ContainerIterator<T> begin, ContainerIterator<T> root, std::size_t count, Compare comp)
		{
			ContainerIterator<T> largest = root;
			ContainerIterator<T> i = begin + (2 * (root - begin) + 1);
			ContainerIterator<T> j = begin + (2 * (root - begin) + 2);
			if (i < begin + count && comp(*largest, *i))
			{
				largest = i;
			}
			if (j < begin + count && comp(*largest, *j))
			{
				largest = j;
			}
			if (largest != root)
			{
				Swap(*root, *largest);
				Heapify(begin, largest, count, comp);
			}
		}
	}
	template<typename T, typename Compare = std::less<T>>
	inline void HeapSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare{})
	{
		int count = (end - begin);
		if (count <= 1)
		{
			return;
		}

		for (ContainerIterator<T> iter = begin + (count / 2) - 1; iter >= begin; --iter)
		{
			HeapSortHelpers::Heapify(begin, iter, count, comp);
		}
		for (ContainerIterator<T> iter = end - 1; iter > begin; --iter)
		{
			Swap(*begin, *iter);
			HeapSortHelpers::Heapify(begin, begin, iter - begin, comp);
		}

	}
	namespace IntroSortHelpers
	{
		template<typename T, typename Compare>
		void IntroSortUtil(ContainerIterator<T> begin, ContainerIterator<T> end, int depthLimit, Compare comp)
		{
			std::size_t count = end - begin;
			if (count < 16)
			{
				InsertionSort(begin, end, comp);
				return;
			}
			if (depthLimit <= 0)
			{
				HeapSort(begin, end, comp);
				return;
			}
			ContainerIterator<T> p = QuickSortHelpers::Partition(begin, end, comp);
			IntroSortUtil(begin, p, depthLimit - 1, comp);
			IntroSortUtil(p + 1, end, depthLimit - 1, comp);
		}
	}
	template<typename T, typename Compare = std::less<T>>
	inline void IntroSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare{})
	{
		std::size_t count = end - begin;
		if (count > 1)
		{
			int depthLimit = 2 * std::log2(count);
			IntroSortHelpers::IntroSortUtil(begin, end, depthLimit, comp);
		}
	}
}

#endif // !__GLOBAL_HEADER__