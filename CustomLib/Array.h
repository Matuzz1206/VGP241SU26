#pragma once

#include <cstddef>
#include <utility>

template<typename T, std::size_t N>
class Array
{
public:
	//Base constructor, called by default
	Array()
	{
		//will generate a dimension
		static_assert(N > 0, "Array size must be greater than 0");
		//allocate memory
		//size required is size of T, which is a type of the object
		//* the number of times, N
		mValues = new T[N];
	}
	Array(T initialValue)
	{
		static_assert(N > 0, "Array size must be greater than 0");
		mValues = new T[N];
		for (std::size_t i = 0; i < N; ++i)
		{
			mValues[i] = initialValue;
		}
	}
	//destructor
	~Array()
	{
		if(mValues != nullptr)
		{
			delete[] mValues;
			mValues = nullptr;
		}
	}
	//copy constructor(called on creation)
	//copies the information of another same sized array
	Array(const Array& other)
	{
		mValues = new T[N];
		for (std::size_t i = 0; i < N; ++i)
		{
			mValues[i] = other.mValues[i];
		}
	}
	//copy operator (after creation, so may have data)
	//copies the information of another same sized array
	Array& operator=(const Array& other)
	{
		//if you have an array of objects that have pointers or data,
		//that data needts to be released or memory leak
		if(mValues != nullptr)
		{
			delete[] mValues;
		}
		mValues = new T[N];
		for (std::size_t i = 0; i < N; ++i)
		{
			mValues[i] = other.mValues[i];
		}
		return *this;
	}
	//Move constructor (called on creation)
	Array(Array&& other) 
	{
		//not deleting the data, changing ownership
		mValues = std::move(other.mValues);
		//clearing the info
		other.mValues = nullptr;
	}
	//move operator (called after creation)
	Array& operator=(Array&& other)
	{
		if(mValues != nullptr)
		{
			delete[] mValues;
		}
		mValues = std::move(other.mValues);
		other.mValues = nullptr;
		return *this;
	}
	//get the number of elements (make it const after the function so it can be called if array is const)
	const std::size_t Size() const
	{
		return N;
	}
	//get the stored data
	T* Data() 
	{
		return mValues;
	}
	//const value
	const T* Data() const
	{
		return mValues;
	}
	//operator overload []
	T& operator[](std::size_t index)
	{
		//can throw assert if out of range
		return mValues[index];
	}
	const T& operator[](std::size_t index) const
	{
		return mValues[index];
	}

private:
	//T is the type we declare
	//pointer to a section of memory where the array is built
	T* mValues = nullptr;
};
