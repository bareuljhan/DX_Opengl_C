#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// Stack
// Queue 조사하기

template<typename T, typename Container = deque<T>>

class Stack
{
public:
	Stack() { v.clear(); }
	~Stack() {}

	void push(const int& value)
	{
		v.push_back(value);
	}
	void pop()
	{
		v.pop_back();
	}

	const int& top()
	{
		return v.back();
	}

	bool empty()
	{

		return v.size() == 0;
	}

	size_t size()
	{
		return v.size();
	}
private:
	vector<T> v;
};


class Queue
{
public:
	void push(const int& value)
	{
		v.push_front(value);
	}

	void pop()
	{
		v.pop_front();
	}
	
	bool empty()
	{
		return v.size() == 0;
	}

	const int& front()
	{
		return v.front();
	}

private:
	list<int> v;
};

int main()
{
	stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);
	s.push(6);

	while (true)
	{
		if (s.empty() == true)
			break;

		// stack 관련 데이터를 활용
		cout << s.top() << endl;

		s.pop();
	}


	cout << "-------- Queue --------" << endl;

	Queue q;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	q.push(6);

	while (true)
	{
		if (q.empty() == true)
		{
			break;

			cout << q.front() << endl;
			q.pop();
		}
	}
	q.pop();
	
}