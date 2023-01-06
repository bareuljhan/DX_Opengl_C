#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>

using namespace std;

// LIS (Longest Increasing Sequence) : �κ� ���� �������� ���� �� ���� ���̸� ã�´�.

// Seq : 1 2 9 5 8 10
// 1 2 5 (�κм���)
// 5 8 10 (�κм���)
// 10 5 1 (X)

// ���� �κ� ����
// 1 2 5 (0)
// 2 9 5 (X)
// 1 2 5 8 10 ->

vector<int> seq = { 5,1,2,3,1 };
vector<int> cache = vector<int>(100, -1);

int LIS(int pos)
{
	// ��������
	if (pos == seq.size() - 1)
		return 1;

	// ĳ��
	int& ref = cache[pos];

	if (ref != -1)
		return ref;

	cache[pos] = 1;

	// ���ϱ�
	// LIS(0) = LIS(1) + 1;
	for (int next = pos + 1; next < seq.size(); next++)
	{
		if (seq[pos] < seq[next])
		{
			ref = max(ref, LIS(next) + 1);
		}
	}

	return ref;
}

int main()
{
	int lis = 0;
	
	for (int i = 0; i < seq.size(); i++)
	{
		lis = max(lis, LIS(i));
	}

	cout << lis << endl;

	return 0;
}