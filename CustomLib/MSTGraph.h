#pragma once

#include "PriorityQueue.h"

template<typename T, typename W = int>
class MSTGraph
{
private:
	struct Neighbor
	{
		int index = -1;
		W weight;

		bool operator<(const Neighbor& rhs) const { return weight < rhs.weight; }
		bool operator<=(const Neighbor& rhs) const { return weight <= rhs.weight; }
		bool operator==(const Neighbor& rhs) const { return weight == rhs.weight; }
		bool operator>=(const Neighbor& rhs) const { return weight >= rhs.weight; }
		bool operator>(const Neighbor& rhs) const { return weight > rhs.weight; }
	};
	struct Node
	{
		const T* data = nullptr;
		Vector<Neighbor> neighbors;
		W bestWeight;
		bool isVisited = false;
		bool isAdded = false;
	};
public:
	MSTGraph()
	{

	}
	~MSTGraph()
	{
		Terminate();
	}

	std::size_t AddItem(const T* data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		mNodes.PushBack(newNode);
		return mNodes.Size() - 1;
	}
	void AddLink(std::size_t from, std::size_t to, W weight, bool biDirectional = true)
	{
		if (from >= mNodes.Size() || to >= mNodes.Size())
		{
			return;
		}
		Neighbor neighbor = { to, weight };
		mNodes[from]->neighbors.PushBack(neighbor);

		if (biDirectional)
		{
			neighbor.index = from;
			mNodes[to]->neighbors.PushBack(neighbor);
		}
	}
	void ObtainMST(int start, Vector<const T*>& mst, Vector<const T*>& links, W& totalWeight)
	{

		Reset();
		links.Resize(mNodes.Size(), nullptr);
		PriorityQueue<Neighbor, std::greater<Neighbor>> process;
		process.Push({ start,0 });
		while (!process.Empty())
		{
			Neighbor neighbor = process.Top();
			process.Pop();
			Node* node = mNodes[neighbor.index];
			if (!node->isVisited)
			{
				node->isVisited = true;
				totalWeight += neighbor.weight;
				mst.PushBack(node->data);
				for (std::size_t i = 0; i < node->neighbors.Size(); ++i)
				{
					const Neighbor& toNeighbor = node->neighbors[i];
					Node* toNode = mNodes[toNeighbor.index];
					if (!toNode->isVisited && (!toNode->isAdded || toNeighbor.weight < toNode->bestWeight))
					{
						links[toNeighbor.index] = node->data;
						toNode->isAdded = true;
						toNode->bestWeight = toNeighbor.weight;
						process.Push(toNeighbor);
					}
				}
			}
		}
	}

	void Terminate()
	{
		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			delete mNodes[i];
			mNodes[i] = nullptr;

		}
		mNodes.Clear();
	}
private:

	void Reset()
	{
		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			mNodes[i]->isVisited = false;
			mNodes[i]->isAdded = false;
		}
	}
	Vector<Node*> mNodes;
};