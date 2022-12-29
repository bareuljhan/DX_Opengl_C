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
	// ���� ��ȸ : ��Ʈ -> ���� -> ������
	// ���� ��ȸ : ���� -> ��Ʈ -> ������
	// ���� ��ȸ : ���� -> ������ -> ��Ʈ

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
	

	//if (node->left != nullptr) => ����Լ�
	//	return Min(node->left);
	//return node;

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

	//if (node->right != nullptr) => ����Լ�
	//	return Max(node->left);
	//return node;

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
		return Max(node->left);
	}
	else
		return nullptr;
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node == nullptr)
		return node;

	if (node->right != nullptr)
	{
		Min(node->right);
	}
	else return nullptr;
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	if (node->left == nullptr)
		Replace(node, node->right);
	else if (node->right == nullptr)
		Replace(node, node->left);
	else
	{
		Node* prev = Previous(node);
		node->key = prev->key;
		node->data = prev->data;
		Delete(prev);
	}
}

void BinarySearchTree::Replace(Node* node1, Node* node2)
{
	// node1�� ��Ʈ�� ��
	if (node1->parent == nullptr)
		_root = node2;

	// node1�� �θ��ʿ��� ���ʿ� �ִ� ���� ��
	else if (node1 == node1->parent->left)
	{
		node1->parent->left = node2;
	}
	// node1�� �θ��ʿ��� �����ʿ� �ִ� ���� ��
	else
	{
		node1->parent->right = node2;
	}

	if(node2 != nullptr)
		node2->parent = node1->parent;

	delete node1;
}