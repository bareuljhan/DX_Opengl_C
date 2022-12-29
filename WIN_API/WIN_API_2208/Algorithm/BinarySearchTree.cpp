#include <iostream>

using namespace std;

#include "BinarySearchTree.h"

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node(key);

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}
	Node* node = _root;
	Node* parent = nullptr;

	while (true)
	{
		if (node == nullptr)
			break;
		parent = node;
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	newNode->parent = parent;
	if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;
}

void BinarySearchTree::PrintTree(Node* node)
{
	// 전위 순회 : 루트 -> 왼쪽 -> 오른쪽
	// 중위 순회 : 왼쪽 -> 루트 -> 오른쪽
	// 후위 순회 : 왼쪽 -> 오른쪽 -> 루트

	if (node == nullptr)
		return;

	cout << node->key << endl;
	PrintTree(node->left);
	PrintTree(node->right);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == nullptr)
		return node;

	if (node->key == key)
		return node;

	if (node->key > key)
	{
		return Search(node->left, key);
	}
	else
	{
		return Search(node->right, key);
	}
}

Node* BinarySearchTree::Min(Node* node)
{
	if (node == nullptr)
	{
		return node;
	}

	while (true)
	{
		if (node->left == nullptr)
		{
			return node;
		}
		node = node->left;
	}
}

Node* BinarySearchTree::Max(Node* node)
{
	if (node == nullptr)
		return node;

	while (true)
	{
		if (node->right == nullptr)
		{
			return node;
		}
		node = node->right;
	}
}

Node* BinarySearchTree::Previous(Node* node)
{
	if (node == nullptr)
		return node;

	if (node->left != nullptr)
	{
		if (Max(node->left) == nullptr)
			return node->left;
		else
			return Max(node->left);
	}

	while (node->parent != nullptr && node == node->parent->left)
	{
		node = node->parent;
		node->parent = node->parent->parent;
	}
	return node->parent = node->parent->parent;
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node == nullptr)
		return node;

	if (node->right != nullptr)
	{
		if (Min(node->right) == nullptr)
			return node->right;
		else
			return Min(node->right);
	}

	while (node->parent != nullptr && node == node->parent->right)
	{
		node = node->parent;
		node->parent = node->parent->parent;
	}
	return node->parent = node->parent->parent;
}
