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
	while (true)
	{
		if (node->key == key)
			break;
		if (node->left->key <= key)
		{
			if (node->left->key == key)
			{
				node = node->left;
				break;
			}
			else
				Search(node->left, key);
		}
		if (node->right->key == key)
		{
			if (node->right->key == key)
			{
				node = node->right;
				break;
			}
			else
				Search(node->right, key);
		}
	}
	return node;
}

Node* BinarySearchTree::Min(Node* node)
{
	// 얘 부터 다시
	while (true)
	{
		if (node->left == nullptr)
			node = node->left;
			break;
		if (node > node->left)
		{
			Min(node);
		}
	}
	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	while (true)
	{
		if (node->right == nullptr)
			break;
	}
	return nullptr;
}

Node* BinarySearchTree::Previous(Node* node)
{
	return nullptr;
}

Node* BinarySearchTree::Next(Node* node)
{
	return nullptr;
}
