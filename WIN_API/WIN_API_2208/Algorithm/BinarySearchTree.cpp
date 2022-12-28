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

Node* BinarySearchTree::Search(Node* root, int key)
{
	// 
	return nullptr;
}

Node* BinarySearchTree::Min(Node* root)
{
	return nullptr;
}

Node* BinarySearchTree::Max(Node* root)
{
	return nullptr;
}

Node* BinarySearchTree::Previous(Node* root)
{
	return nullptr;
}

Node* BinarySearchTree::Next(Node* node)
{
	return nullptr;
}
