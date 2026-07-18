#pragma once

#include <algorithm>
#include <iterator>
#include <cstddef>

template<typename T>
class ContainerIterator
{
public:
	// Stl uses
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using differece_type = std::ptrdiff_t;
	using pointer = T*;
	using referenece = T&;

	ContainerIterator(T* ptr) : mPtr(ptr)
	{
	}
	T& operator*() { return *mPtr; }
	T* operator->() { return mPtr; }

	// ++iter
	ContainerIterator& operator++() { ++mPtr; return *this; }
	// --iter
	ContainerIterator& operator--() { --mPtr; return *this; }
	// iter++
	ContainerIterator operator++(int) { ContainerIterator tmp = *this; ++(*this); return *tmp; }
	// iter-
	ContainerIterator operator--(int) { ContainerIterator tmp = *this; --(*this); return *tmp; }

	ContainerIterator operator+(differece_type n) const { return ContainerIterator(mPtr + n); }
	ContainerIterator operator-(differece_type n) const { return ContainerIterator(mPtr - n); }
	ContainerIterator& operator+=(differece_type n) { mPtr += n; return this; }
	ContainerIterator& operator-=(differece_type n) { mPtr -= n; return this; }

	differece_type operator-(const ContainerIterator& rhs) const { return mPtr - rhs.mPtr; }
	//Comparisons
	bool operator==(const ContainerIterator& rhs) const { return mPtr == rhs.mPtr; }
	bool operator!=(const ContainerIterator& rhs) const { return mPtr != rhs.mPtr; }
	bool operator<(const ContainerIterator& rhs) const { return mPtr < rhs.mPtr; }
	bool operator>(const ContainerIterator& rhs) const { return mPtr > rhs.mPtr; }
	bool operator<=(const ContainerIterator& rhs) const { return mPtr <= rhs.mPtr; }
	bool operator>=(const ContainerIterator& rhs) const { return mPtr >= rhs.mPtr; }

private:
	T* mPtr = nullptr;
};