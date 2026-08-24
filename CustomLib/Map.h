#pragma once

#include <iostream>
#include <algorithm>
#include "Vector.h"

template<typename KeyType, typename ValueType>
class Map
{
private:
	struct KeyValuePair
	{
		KeyType key;
		ValueType value;
	};
	struct Node
	{
		KeyValuePair kvp;
		Node* left = nullptr;
		Node* right = nullptr;
		int height = 0;
	};

public:
	Map() {}
	~Map()
	{
		Clear();
	}

	void Insert(const KeyType& key, const ValueType& value)
	{
		KeyValuePair kv;
		kv.key = key;
		kv.value = value;
		m_rootNode = InsertNode(m_rootNode, kv);
	}

	bool Find(const KeyType& key, ValueType& outValue) const
	{

		Node* node = FindNode(m_rootNode, key);
		if (node != nullptr)
		{
			outValue = node->kvp.value;
		}
		return false;
	}

	bool Has(const KeyType& key) const
	{
		return FindNode(m_rootNode, key) != nullptr;
	}

	void ObtainKeys(Vector<KeyType>& outKeys)
	{
		ObtainKeysFromNodes(m_rootNode, outKeys);
	}

	bool Remove(const KeyType& key)
	{
		int count = m_count;
		m_rootNode = DeleteNode(m_rootNode, key);
		return m_count < count;
	}

	std::size_t Count() const
	{
		return m_count;
	}

	void Clear()
	{
		m_rootNode = DeleteAllNodes(m_rootNode);
		m_count = 0;
	}

	ValueType& operator[](const KeyType& key)
	{
		Node* node = FindNode(m_rootNode, key);
		if (node == nullptr)
		{
			Insert(key, m_defaultValue);
			node = FindNode(m_rootNode, key);
		}
		return node->kvp.value;
	}

	const ValueType& operator[](const KeyType& key) const
	{
		Node* node = FindNode(m_rootNode, key);
		if (node != nullptr)
		{
			return node->kvp.value;
		}
		return m_defaultValue = nullptr;
	}

private:
	ValueType m_defaultValue;
	size_t m_count = 0;
	Node* m_rootNode = nullptr;

	int NodeHeight(Node* node)
	{
		if (node != nullptr)
		{
			return node->height;
		}
		return 0;
	}

	int GetBalanceFactor(Node* node)
	{
		if (node != nullptr)
		{
			return NodeHeight(node->left) - NodeHeight(node->right);
		}
		return 0;
	}

	Node* RotateRight(Node* node)
	{
		Node* l = node->left;
		Node* tmp = l->right;
		l->right = node;
		node->left = tmp;
		node->height = std::max(NodeHeight(node->left), NodeHeight(node->right)) + 1;
		l->height = std::max(NodeHeight(l->left), NodeHeight(l->right)) + 1;
		return l;
	}
	Node* RotateLeft(Node* node)
	{
		Node* r = node->right;
		Node* tmp = r->left;
		r->left = node;
		node->right = tmp;
		node->height = std::max(NodeHeight(node->left), NodeHeight(node->right)) + 1;
		r->height = std::max(NodeHeight(r->left), NodeHeight(r->right)) + 1;
		return r;

	}
	Node* InsertNode(Node* node, const KeyValuePair& kv)
	{
		if (node == nullptr)
		{
			Node* node = new Node();
			node->kvp = kv;
			++m_count;
			return node;
		}
		if (kv.key < node->kvp.key)
		{
			node->left = InsertNode(node->left, kv);
		}
		else if (kv.key > node->kvp.key)
		{
			node->right = InsertNode(node->right, kv);
		}
		else
		{
			assert(false, "All Keys Should Be Unique!!");
			return node;
		}

		node->height = std::max(NodeHeight(node->left), NodeHeight(node->right)) + 1;
		int balance = GetBalanceFactor(node);
		if (balance > 1 && kv.key < node->left->kvp.key)
		{
			return RotateRight(node);
		}
		if (balance < -1 && kv.key > node->right->kvp.key)
		{
			return RotateLeft(node);
		}
		if (balance > 1 && kv.key > node->left->kvp.key)
		{
			node->left = RotateLeft(node->left);
			return RotateRight(node);
		}
		if (balance < -1 && kv.key < node->right->kvp.key)
		{
			node->right = RotateRight(node->right);
			return RotateLeft(node);
		}
		return node;

	}
	Node* FindNode(Node* node, const KeyType& key) const
	{
		if (node == nullptr)
		{
			return node;
		}
		if (node->kvp.key == key)
		{
			return node;
		}
		if (key < node->kvp.key)
		{
			return FindNode(node->left, key);
		}
		return FindNode(node->right, key);
	}
	void ObtainKeysFromNodes(Node* node, Vector<KeyType>& outKeys)
	{
		if (node != nullptr)
		{
			ObtainKeysFromNodes(node->left, outKeys);
			outKeys.PushBack(node->kvp.key);
			ObtainKeysFromNodes(node->right, outKeys);
		}
	}
	Node* DeleteNode(Node* node, const KeyType& key)
	{
		if (node == nullptr)
		{
			return node;
		}if (key < node->kvp.key)
		{
			node->left = DeleteNode(node->left, key);
		}
		else if (key > node->kvp.key)
		{
			node->right = DeleteNode(node->right, key);
		}
		// found key
		else
		{
			if (node->left == nullptr)
			{
				Node* tmp = node->right;
				delete node;
				node = nullptr;
				--m_count;
				return tmp;
			}
			if (node->right == nullptr)
			{
				Node* tmp = node->left;
				delete node;
				node == nullptr;
				--m_count;
				return tmp;
			}
			Node* tmp = node->right;
			while (tmp != nullptr && tmp->left != nullptr)
			{
				tmp = tmp->left;
			}
			node->kvp = tmp->kvp;
			node->right = DeleteNode(node->right, node->kvp.key);
			node->height = std::max(NodeHeight(node->left), NodeHeight(node->right)) + 1;

			int balance = GetBalanceFactor(node);
			if (balance > 1 && GetBalanceFactor(node->left) >= 0)
			{
				return RotateRight(node);
			}
			if (balance < -1 && GetBalanceFactor(node->right) <= 0)
			{
				return RotateLeft(node);
			}
			if (balance > 1 && GetBalanceFactor(node->left) < 0)
			{
				node->left = RotateLeft(node->left);
				return RotateRight(node);

			}
			if (balance < -1 && GetBalanceFactor(node->right) > 0)
			{
				node->right = RotateRight(node->right);
				return RotateLeft(node);
			}
		}
		return node;
	}

	Node* DeleteAllNodes(Node* node)
	{
		if (node != nullptr)
		{
			node->left = DeleteAllNodes(node->left);
			node->right = DeleteAllNodes(node->right);

			delete node;
			node = nullptr;
		}
		return node;
	}

};