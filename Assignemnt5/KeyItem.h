#pragma once
#include <string>
#include <iostream>

class KeyItem
{
public:
	KeyItem() = default;
	KeyItem(const std::string& name, int count = 0)
		: mName(name)
		, mCount(count)
	{
	}
	void Add(int amount)
	{
		mCount += amount;
	}
	void Consume(int amount)
	{
		mCount -= amount;
	}
	int GetCount() const
	{
		return mCount;
	}
	const std::string& GetName() const
	{
		return mName;
	}
	void Print() const
	{
		std::cout << mName << ": " << mCount << std::endl;
	}
private:
	std::string mName;
	int mCount = 0;
};