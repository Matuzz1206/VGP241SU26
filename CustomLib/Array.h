#pragma once

#include  <cstddef>
#include  <utility>
#include "ContainerIterator.h"
template <typename T, std::size_t N>
class Array {
public:
	//base constructor, called by default
	Array() {
		// will generate a dimension
		static_assert(N > 0, "Array must be at least 1");
		//allocate memory
		//size required is size of T * N
		mValues = new T[N];
	}
	Array(T initialValue) {
		static_assert(N > 0, "Array must be at least 1");
		mValues = new T[N];
		for (std::size_t i = 0; i < N; i++) {
			mValues[i] = initialValue;
		}
	}
	~Array() {
		if (mValues != nullptr) {
			delete[] mValues;
			mValues = nullptr;
		}

	}
	//copy constructor
	Array(const Array<T, N>& other) {
		mValues = new T[N];
		for (std::size_t i = 0; i < N; i++) {
			mValues[i] = other.mValues[i];
		}
	}
	//copy operator
	Array& operator=(const Array& other) {
		if (mValues != nullptr) {
			delete[] mValues;
		}
		mValues = new T[N];
		for (std::size_t i = 0; i < N; i++) {

			mValues[i] = other.mValues[i];
		}
		return *this;
	}
	//move constructor
	Array(Array&& other) {
		mValues = std::move(other.mValues);
		other.mValues = nullptr;
	}

	Array& operator=(Array&& other) {
		if (mValues != nullptr) {
			delete[] mValues;
		}
		mValues = std::move(other.mValues);
		other.mValues = nullptr;
		return *this;
	}
	const std::size_t Size() const {
		return N;
	}
	T* Data() {
		return mValues;
	}
	const T* Data() const {
		return mValues;
	}
	//operator overload []
	T& operator[](std::size_t index) {
		return mValues[index];
	}
	const T& operator[](std::size_t index) const {
		return mValues[index];
	}

	//iterator definitions
	using Iterator = ContainerIterator<T>;
	using Const_Iterator = ContainerIterator<const T>;
	Iterator Begin() { return Iterator(mValues); }
	Iterator End() { return Iterator(mValues + N); }
	Const_Iterator Begin() const { return Const_Iterator(mValues); }
	Const_Iterator End() const { return Const_Iterator(mValues + N); }
private:
	//T is the type we declare
	T* mValues = nullptr;

};