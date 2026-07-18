#pragma once
#include <cstddef>
#include <utility>
#include <cassert>
#include "ContainerIterator.h"
template <typename T>
class Vector
{
public:
	Vector() : mValues(nullptr), mSize(0), mCapacity(0) {

	}
	~Vector() {
		if (mValues != nullptr) {
			delete[] mValues;
			mValues = nullptr;
		}
	}
	Vector(const Vector<T>& other) {
		if (other.mCapacity > 0) {
			mValues = new T[other.mCapacity];
			for (std::size_t i = 0; i < other.mCapacity; i++)
			{
				mValues[i] = other.mValues[i];

			}
			mCapacity = other.mCapacity;
			mSize = other.mSize;
		}
	}
	Vector& operator=(const Vector<T>& other) {
		if (mValues != nullptr) {
			delete[] mValues;
			mValues = nullptr;
		}
		if (other.mCapacity > 0) {
			mValues = new T[other.mCapacity];
			for (std::size_t i = 0; i < other.mCapacity; i++)
			{
				mValues[i] = other.mValues[i];

			}
			mCapacity = other.mCapacity;
			mSize = other.mSize;
		}
		return *this;
	}
	Vector(Vector&& other) {
		mValues = std::move(other.mValues);
		mCapacity = std::move(other.mCapacity);
		mSize = std::move(other.mSize);

		other.mValues = nullptr;
		other.mCapacity = 0;
		other.mSize = 0;
	}
	Vector& operator=(Vector&& other) {
		if (mValues != nullptr) {
			delete[] mValues;
			mValues = nullptr;
		}
		mValues = std::move(other.mValues);
		mCapacity = std::move(other.mCapacity);
		mSize = std::move(other.mSize);

		other.mValues = nullptr;
		other.mCapacity = 0;
		other.mSize = 0;
		return *this;
	}
	void Reserve(std::size_t newCapacity) {
		if (newCapacity > mCapacity) {
			T* values = new T[newCapacity];
			if (mValues != nullptr) {
				for (size_t i = 0; i < mSize; i++)
				{
					values[i] = mValues[i];

				}

			}
			delete[] mValues;
			mValues = std::move(values);
			mCapacity = newCapacity;
		}
	}
	void Resize(std::size_t size, const T& initialValue = T()) {
		if (size == mSize) {
			return;
		}
		if (size < mSize) {
			for (size_t i = size; i < mSize; i++)
			{
				mValues[i].~T();
			}
		}
		else if (mSize < size)
		{
			std::size_t newCapacity = std::max(size, mCapacity * 2);
			Reserve(newCapacity);
			for (size_t i = mSize; i < size; ++i)
			{
				mValues[i] = initialValue;
			}
		}
		mSize = size;
	}
	void Clear() {
		Resize(0);
	}
	std::size_t Size() const {
		return mSize;
	}
	std::size_t Capacity() const {
		return mCapacity;
	}
	void PushBack(const T& value) {
		if (mSize >= mCapacity) {
			std::size_t newCapacity = (mCapacity == 0) ? 1 : mCapacity * 2;
			Reserve(newCapacity);
		}
		mValues[mSize] = value;
		++mSize;
	}
	void PopBack() {
		assert(mSize > 0, "Vector is empty");
		Resize(mSize - 1);
	}
	T& operator[](std::size_t index) {
		assert(index < mSize, "Index out of bounds");
		return mValues[index];
	}
	const T& operator[](std::size_t index) const {
		assert(index < mSize, "Index out of bounds");
		return mValues[index];
	}

	//iterator definitions
	using Iterator = ContainerIterator<T>;
	using Const_Iterator = ContainerIterator<const T>;
	Iterator Begin() { return Iterator(mValues); }
	Iterator End() { return Iterator(mValues + mSize); }
	Const_Iterator Begin() const { return Const_Iterator(mValues); }
	Const_Iterator End() const { return Const_Iterator(mValues + mSize); }
private:
	T* mValues = nullptr;
	std::size_t mSize = 0;
	std::size_t mCapacity = 0;

};