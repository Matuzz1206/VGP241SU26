#pragma once

#include "Vector.h"

template <typename T>
class Stack {
public:
	void Push(const T& value)
	{
		mValues.PushBack(value);
	}
	void Pop()
	{
		assert(!Empty() && "[Error] Trying to pop an empty stack");
		mValues.PopBack();
	}

	const T& Top() const
	{
		assert(!Empty() && "[Error] Trying to view of an empty stack");
		return mValues[Size() - 1];
	}

	std::size_t Size() const
	{
		return mValues.Size();
	}
	bool Empty() const
	{
		return mValues.Size() == 0;
	}
private:
	Vector<T> mValues;
};