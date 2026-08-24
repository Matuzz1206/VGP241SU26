#pragma once

#include <algorithm>
#include <functional>
#include "Vector.h"

template<typename KeyType, typename ValueType>
class UnorderedMap
{
private:
	struct KeyValuePair
	{
		KeyType key;
		ValueType value;
	};

public:
	UnorderedMap(std::size_t initialBucketSize = 8, double loadFactor = 0.8)
		: m_loadFactorThreshold(loadFactor), m_count(0)
	{
		m_bucketCount = std::max<size_t>(initialBucketSize, 1);
		m_table.Resize(m_bucketCount);
	}

	// delete copy/moves
	// prevents duplicating
	UnorderedMap(const UnorderedMap&) = delete;
	UnorderedMap(UnorderedMap&&) = delete;
	UnorderedMap& operator=(const UnorderedMap&) = delete;
	UnorderedMap& operator=(UnorderedMap&&) = delete;

	void Insert(const KeyType& key, const ValueType& value)
	{
		size_t index = GetTableIndex(key);
		// check if something is there
		Vector<KeyValuePair*>& bucket = m_table[index];
		for (size_t i = 0; i < bucket.Size(); i++)
		{
			if (bucket[i]->key == key)
			{
				// if already added, update the value and return
				bucket[i]->value;
				return;
			}
		}
		// Otherwise add the new key and keyvalue pair
		KeyValuePair* kv = new KeyValuePair();
		kv->key = key;
		kv->value = value;
		m_table[index].PushBack(kv);
		++m_count;

		if ((double)m_count / (double)m_bucketCount > m_loadFactorThreshold)
		{
			// if too many items, very possible too many collisions, resize and rehash index locations
			Rehash();
		}
	}

	bool Find(const KeyType& key, ValueType& outValue) const
	{
		size_t index = GetTableIndex(key);
		const Vector<KeyValuePair*>& bucket = m_table[index];
		for (size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				outValue = bucket[i]->value;
				return true;
			}
		}
		return false;
	}

	bool Has(const KeyType& key) const
	{
		std::size_t index = GetTableIndex(key);
		const Vector<KeyValuePair*>& bucket = m_table[index];
		for (size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				return true;
			}
		}
		return false;
	}

	bool Remove(const KeyType& key)
	{
		size_t index = GetTableIndex(key);
		Vector<KeyValuePair*>& bucket = m_table[index];
		for (size_t i = 0; i < bucket.Size(); i++)
		{
			if (bucket[i]->key == key)
			{
				// delete the item
				// swap to the back
				KeyValuePair* tmp = bucket[i];
				bucket[i] = bucket[bucket.Size() - 1];
				bucket[bucket.Size() - 1] = tmp;
				// delete the data
				delete tmp;
				tmp = nullptr;
				// pop off the bucket
				bucket.PopBack();
				return true;
			}
		}
		return false;
	}

	size_t Count() const
	{
		return m_count;
	}

	void Clear()
	{
		for (size_t t = 0; t < m_table.Size(); ++t)
		{
			Vector<KeyValuePair*>& bucket = m_table[t];
			for (size_t b = 0; b < bucket.Size(); ++b)
			{
				delete bucket[b];
				bucket[b] = nullptr;
			}
			bucket.Clear();
		}
		m_count = 0;
	}

	// data accessors (operatos)
	ValueType& operator[](const KeyType& key)
	{
		// if i do have it, return reference
		if (!Has(key))
		{
			// insert default so there is a value
			Insert(key, m_default);
		}

		size_t index = GetTableIndex(key);
		Vector<KeyValuePair*>& bucket = m_table[index];
		for (size_t i = 0; i < bucket.Size(); i++)
		{
			if (bucket[i]->key == key)
			{
				return bucket[i]->value;
			}
		}

		assert(false, "UnorderedMap: Key never gets added");
		return m_default;
	}

	const ValueType& operator[](const KeyType& key) const
	{
		size_t index = GetTableIndex(key);
		Vector<KeyValuePair*>& bucket = m_table[index];
		for (size_t i = 0; i < bucket.Size(); i++)
		{
			if (bucket[i]->key == key)
			{
				return bucket[i]->value;
			}
		}
		return m_default;
	}

private:
	size_t GetTableIndex(const KeyType& key) const
	{
		// if there si a resize, need to remove and re add all elements
		// the table index WILL change because the m_bucketCount will increase
		return m_hashFunction(key) % m_bucketCount;
	}

	void Rehash()
	{
		// we will remove al items and add in the updated  table indices
		size_t newBucketCount = m_bucketCount * 2;
		Vector<Vector<KeyValuePair*>> newTable;
		newTable.Resize(newBucketCount);

		// need to get everything from theold table, resposition and swpp data over
		// update bucket count before swapping to make sure new index is correct

		m_bucketCount = newBucketCount;
		for (size_t t = 0; t < m_table.Size(); t++)
		{
			Vector<KeyValuePair*>& bucket = m_table[t];
			for (size_t b = 0; b < bucket.Size(); b++)
			{
				size_t index = GetTableIndex(bucket[b]->key);
				newTable[index].PushBack(bucket[b]);
			}
			bucket.Clear();
		}
		m_table = std::move(newTable);
		newTable.Clear();
	}


	// This is used if something can't be found and you can't return a nullptr
	ValueType m_default;
	// Table is the main vector, "Bucket" is the vector of objects using the same index
	Vector<Vector<KeyValuePair*>> m_table;
	// Max indices the table can use to store individual values
	size_t m_bucketCount = 0;
	// total number of items in the table
	size_t m_count = 0;
	// how many items in the bucket before we need to risze the table
	double m_loadFactorThreshold = 1.0;
	// stl version of hashFunctin to allow any atype of key value to be hashed
	std::hash<KeyType> m_hashFunction;



};