#pragma once
class DisJointSet
{
public:
	DisJointSet(int n)
		:_parent(n, 0)
		, _rank(n, 1)
	{

	}


	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;
		int parent = _parent[u];
		return FindLeader(parent);
	}

	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if (uLeader == vLeader)
			return;

		if (_rank[uLeader] > _rank[vLeader])
		{
			std::swap(uLeader, vLeader);
		}
		_parent[uLeader] = vLeader;

		if (_rank[uLeader] == _rank[vLeader])
			_rank[vLeader]++;
	}
private:
	vector<int> _parent;
	vector<int> _rank;
};

