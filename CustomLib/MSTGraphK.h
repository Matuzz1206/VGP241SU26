#pragma once
#include "Vector.h"
#include "Global.h"
class DisjointSetUnion
{
public:
	DisjointSetUnion(std::size_t numNodes)
	{
		mParent.Resize(numNodes);
		mRank.Resize(numNodes, 0);
		for (std::size_t i = 0; i < numNodes; ++i)
		{
			mParent[i] = i;
		}
	}
	std::size_t FindParentIndex(std::size_t index)
	{
		if (mParent[index] != index)
		{
			mParent[index] = FindParentIndex(mParent[index]);
		}
		return mParent[index];
	}
	bool UnitEdges(int& from, int& to)
	{
		std::size_t rootFrom = FindParentIndex(from);
		std::size_t rootTo = FindParentIndex(to);
		if (rootFrom == rootTo)
		{
			return false;
		}
		if (mRank[rootFrom] < mRank[rootTo])
		{
			mParent[rootFrom] = rootTo;
		}
		else if (mRank[rootFrom] > mRank[rootTo])
		{
			mParent[rootTo] = rootFrom;
		}
		else
		{
			mParent[rootTo] = rootFrom;
			++mRank[rootFrom];
		}
		return true;
	}
private:
	Vector<int> mParent;
	Vector<int> mRank;
};
template<typename T, typename W = int>
class MSTGraphK
{
private:
	struct Edge
	{
		int from = -1;
		int to = -1;
		W weight;
	};
	struct Node
	{
		const T* data = nullptr;
	};
public:
	MSTGraphK()
	{
	}
	~MSTGraphK()
	{
		Terminate();
	}
	void AddItem(const T* data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		mNodes.PushBack(newNode);
	}
	void AddEdge(std::size_t from, std::size_t to, W weight)
	{
		Edge newEdge = { from, to, weight };
		mEdges.PushBack(newEdge);
	}
	void ObtainMST(Vector<const T*>& mst, Vector<const T*>& links, W& totalWeight)
	{
		std::size_t numNode = mNodes.Size();
		links.Resize(numNode, nullptr);
		DisjointSetUnion dsu(numNode);
		Global::IntroSort(mEdges.Begin(), mEdges.End(),
			[](const Edge& a, const Edge& b)
			{
				return a.weight < b.weight;
			});

		Vector<Vector<int>> adjacency;
		adjacency.Resize(numNode);

		std::size_t edgesUsed = 0;
		for (std::size_t i = 0; i < mEdges.Size() && edgesUsed < numNode - 1; ++i)
		{
			Edge& edge = mEdges[i];
			if (dsu.UnitEdges(edge.from, edge.to))
			{
				totalWeight += edge.weight;
				adjacency[edge.from].PushBack(edge.to);
				adjacency[edge.to].PushBack(edge.from);
				++edgesUsed;
			}
		}
		Vector<bool> visited;
		visited.Resize(numNode, false);
		Vector<std::size_t> stack;
		stack.PushBack(0);
		visited[0] = true;
		mst.PushBack(mNodes[0]->data);
		while (stack.Size() > 0)
		{
			std::size_t current = stack[stack.Size() - 1];
			stack.PopBack();
			for (std::size_t n = 0; n < adjacency[current].Size(); ++n)
			{
				int neighbor = adjacency[current][n];
				if (!visited[neighbor])
				{
					visited[neighbor] = true;
					links[neighbor] = mNodes[current]->data;
					mst.PushBack(mNodes[neighbor]->data);
					stack.PushBack(static_cast<std::size_t>(neighbor));
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
		mEdges.Clear();
	}
private:
	Vector<Node*> mNodes;
	Vector<Edge> mEdges;
};