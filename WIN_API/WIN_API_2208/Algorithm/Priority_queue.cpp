#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// �ִ���
template<typename T, typename Container = vector<T>, typename Pred = less<T>>
class Priority_Queue
{
public:
	void Push(const T& value)
	{
		v.push_back(value);

		// ��Ģ Ȯ��

		int now = static_cast<int>(v.size() - 1); // �� ������

		while (true)
		{
			if (now <= 0)
				break;
			int parent = (now - 1) / 2;

			if (Pred()(v[now], v[parent]))
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
			
			if (Pred()(v[next], v[leftChild]))
				next = leftChild;

			if (rightChild < (int)v.size() && Pred()(v[next], v[rightChild]))
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
	Container v;
};

int main()
{
	priority_queue<int, vector<int>, greater<int>> stdPq;
	Priority_Queue<int, vector<int>, greater<int>> pq;
	stdPq.push(10);
	stdPq.push(7);
	stdPq.push(6);
	stdPq.push(3);
	stdPq.push(15);

	cout << stdPq.top() << endl;
	stdPq.pop();
	cout << stdPq.top() << endl;

	cout << "------" << endl;

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