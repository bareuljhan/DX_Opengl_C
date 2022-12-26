#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// �ִ���
template<class T, vector<T>, greater<T>>
class Priority_Queue
{
public:
	void Push(const T& value)
	{
		v.push_back(value);

		// ��Ģ Ȯ��

		int now = static_cast<T>(v.size() - 1); // �� ������

		while (true)
		{
			if (now <= 0)
				break;
			int parent = (now - 1) / 2;

			if (v[now] < v[parent])
			{
				break;
			}
			std::swap(v[now], v[parent]);
			now = parent;
		}
	}
	
	void pop()
	{
		v[0] = v.back();
		v.pop_back();
		
		// ��Ģ Ȯ��
		int now = 0;
		while (true)
		{
			int leftChild = 2 * now + 1;
			int rightChild = 2 * now + 2;

			if (leftChild >= (int)v.size())
				break;

			int next = now;
			
			if (v[next] < v[leftChild])
				next = leftChild;

			if (rightChild < (int)v.size() && v[next] < v[rightChild])
				next = rightChild;

			if (next == now)
				break;

			std::swap(v[now], v[next]);
			now = next;
		}
	}

	const T& top()
	{
		return v[0];
	}

	bool empty()
	{
		return v.empty();
	}

private:
	vector<T> v;
};

int main()
{
	priority_queue<int, vector<int>, greater<int>> stdPq;
	Priority_Queue pq;

	pq.Push(10);
	pq.Push(7);
	pq.Push(6);
	pq.Push(3);
	pq.Push(15);

	cout << pq.top() << endl;
	pq.pop();
	cout << pq.top() << endl;
	// 1. ������		(qsort, std::sort)
	// 2. ��������	(merge, std::stable_sort)
	// 3. ������		(heap, std::partial_sort)

	return 0;
}