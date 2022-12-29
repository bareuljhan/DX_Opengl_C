#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// ���ý���
// ������ 1000�� ����

struct User
{
	int guild_id;
};

void GuildSystem()
{
	vector<User> users;

	for (int i = 0; i < true; i++)
	{
		users.push_back(User{i});
	}
	// 0 �� ���� : 0
	// 1 �� ���� : 1

	// 1���̶� 5�� ������ ���� ��带 ����� �ʹ�.
	users[1].guild_id = users[5].guild_id;

	// guild�� 2�� �ֶ� 5�� �ֶ� ����
	for (auto& user : users)
	{
		if (user.guild_id == 2)
			user.guild_id = 5;
	}
	// [0] [1] [2] [3] [4] [5]
	//  0	5	5	3	4	5

	// N��° ���̸� ã��ʹ�... -> ��� users[N]
	// ��� ���� -> 0(N)
}

// Ʈ�������� �̿��� ���μ� ����

class DisJointSet
{
public:
	DisJointSet(int n)
	:_parent(n, 0)
	{
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	// ���� �ְ� ������ ������
	int FindLeader(int u)
	{
		// ������� : �ɰ� �� ���� ����
		if (u == _parent[u])
			return u;
		int parent = _parent[u];
		return FindLeader(parent);
	}

	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if (vLeader == uLeader)
			return;

		_parent[uLeader] = vLeader;
	}
private:
	vector<int> _parent;
};
int main()
{
	DisJointSet ds(10);

	cout << ds.FindLeader(5) << endl; // 5

	ds.Merge(0, 5);
	ds.Merge(1, 2);
	ds.Merge(3, 4);
	ds.Merge(0, 3);

	cout << ds.FindLeader(0) << endl;
	ds.Merge(0, 9);
	cout << ds.FindLeader(9) << endl;

	return 0;
}