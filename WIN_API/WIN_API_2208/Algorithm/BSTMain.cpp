#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

#include "BinarySearchTree.h"

// ����Ž��Ʈ��
// - Ž���뵵�� ������� Ʈ��


int main()
{
	BinarySearchTree tree;

	tree.Insert(50);
	tree.Insert(30);
	tree.Insert(70);
	tree.Insert(20);
	tree.Insert(54);
	tree.Insert(40);
	tree.Insert(85);
	tree.Insert(52);
	
	tree.PrintTree(tree._root);

	Node* find = tree.Search(tree._root, 30);
	Node* min = tree.Min(tree._root);
	Node* prev = tree.Previous(tree._root);
	Node* next = tree.Next(tree._root);

	return 0;
}