#pragma once
#include <iostream>
#include <algorithm>
#include <functional>
#include "Vector.h"

template<typename T, std::size_t K>
class KDTree
{
private:
	struct KDNode {
		const T* point = nullptr;
		const void* userData = nullptr;
		KDNode* left = nullptr;
		KDNode* right = nullptr;
	};
public:
	KDTree() {
	}
	~KDTree() {
		Terminate();
	}
	//Add Item, which adds a KDNode
	void AddItem(const T* point, const void* userData) {
		KDNode* newNode = new KDNode();
		newNode->point = point;
		newNode->userData = userData;
		mNodes.PushBack(newNode);
	}
	// Remeve Item, based on user data
	void RemoveItem(const void* userData) {
		std::size_t numNodes = mNodes.Size();
		for (size_t i = 0; i < numNodes; ++i)
		{
			if (mNodes[i]->userData == userData) {
				KDNode* tmp = mNodes[i];
				mNodes[i] = mNodes[numNodes - 1];
				mNodes[numNodes - 1] = tmp;
				delete tmp;
				tmp = nullptr;
				mNodes.PopBack();
				break;
			}
		}
	}
	//
	void BuildTree() {
		Clear(mRoot);
		mRoot = BuildTree(mNodes, 0);
	}

	void FindInRange(Vector<const void*>& result, const T* minRange, const T* maxRange,
		std::function<bool(const void*)> filter = nullptr) {
		FindInRange(result, minRange, maxRange, mRoot, 0, filter);
	}
	const void* FindNearest(const T* target) {
		KDNode* result = FindNearestNode(target, mRoot, 0);
		if (result != nullptr) {
			return result->userData;
		}
		return nullptr;
	}


	void Terminate() {
		for (size_t i = 0; i < mNodes.Size(); ++i)
		{
			delete mNodes[i];
			mNodes[i] = nullptr;
		}
		mNodes.Clear();
	}

private:
	KDNode* BuildTree(Vector < KDNode*>& nodes, int depth) {
		if (nodes.Size() == 0) {
			return nullptr;
		}
		std::sort(nodes.Begin(), nodes.End(),
			[depth](const KDNode* a, const KDNode* b) {
				return a->point[depth] < b->point[depth];
			});

		int median = nodes.Size() / 2;
		KDNode* node = nodes[median];

		Vector<KDNode*> leftPoints;
		Vector<KDNode*> rightPoints;
		leftPoints.Resize(median);
		rightPoints.Resize(nodes.Size() - median - 1);
		int index = 0;
		for (auto iter = nodes.Begin(); iter != nodes.Begin() + median; ++iter) {
			leftPoints[index++] = (*iter);
		}
		index = 0;
		for (auto iter = nodes.Begin() + median + 1; iter != nodes.End(); ++iter) {
			rightPoints[index++] = (*iter);
		}
		node->left = BuildTree(leftPoints, (depth + 1) % K);
		node->right = BuildTree(rightPoints, (depth + 1) % K);

		return node;
	}
	void FindInRange(Vector<const void*>& result, const T* minRange, const T* maxRange,
		KDNode* node, int depth, std::function<bool(const void*)>& filter) {
		if (node == nullptr) {
			return;
		}
		bool isValid = (filter == nullptr || filter(node->userData));
		if (isValid) {
			for (std::size_t i = 0; i < K; i++)
			{
				if (node->point[i] < minRange[i] || node->point[i] > maxRange[i]) {
					isValid = false;
				}
			}
		}
		if (isValid) {
			result.PushBack(node->userData);

		}
		if (minRange[depth] <= node->point[depth]) {
			FindInRange(result, minRange, maxRange, node->left, (depth + 1) % K, filter);
		}
		if (maxRange[depth] >= node->point[depth]) {
			FindInRange(result, minRange, maxRange, node->right, (depth + 1) % K, filter);
		}

	}
	float DistanceSquared(const T* a, const T* b) {
		float distSq = 0.0f;
		for (std::size_t i = 0; i < K; ++i) {
			distSq += (a[i] - b[i]) * (a[i] - b[i]);
		}
		return distSq;
	}
	KDNode* ClosestNode(KDNode* a, KDNode* b, const T* target) {
		if (a == nullptr) {
			return b;
		}if (b == nullptr) {
			return a;
		}

		float aD = DistanceSquared(a->point, target);
		float bD = DistanceSquared(b->point, target);
		if (aD < bD) {
			return a;
		}
		return b;
	}
	KDNode* FindNearestNode(const T* target, KDNode* node, int depth) {
		if (node == nullptr) {
			return nullptr;
		}
		KDNode* nextBranch = nullptr;
		KDNode* otherBranch = nullptr;

		if (target[depth] < node->point[depth]) {
			nextBranch = node->left;
			otherBranch = node->right;
		}
		else {
			otherBranch = node->left;
			nextBranch = node->right;
		}
		KDNode* tmp = FindNearestNode(target, nextBranch, (depth + 1) % K);
		KDNode* best = ClosestNode(tmp, node, target);

		float distSq = DistanceSquared(best->point, target);
		float depthDist = node->point[depth] - target[depth];
		if (distSq > depthDist * depthDist) {
			tmp = FindNearestNode(target, otherBranch, (depth + 1) % K);
			best = ClosestNode(tmp, best, target);
		}
		return best;
	}
	void Clear(KDNode* node) {
		if (node != nullptr) {
			Clear(node->left);
			Clear(node->right);
			node = nullptr;
		}
	}
	Vector<KDNode*> mNodes;
	KDNode* mRoot = nullptr;

};