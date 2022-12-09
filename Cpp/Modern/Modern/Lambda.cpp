#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <array>

using namespace std;

struct Vector2
{
	bool operator <(const Vector2& other)
	{
		float aLength = x * x + y * y;
		float bLength = other.x * other.x + other.y * other.y;

		if (aLength < bLength)
			return true;
		return false;
	}
	int x;
	int y;
};

int main()
{
#pragma region lambda
	vector<int> v;

	for (int i = 0; i < 30; i++)
	{
		if (i % 2 == 0)
		{
			v.push_back(i);
		}
	}
	
	// 25 ���� ū ù��° ������ iter
	// [] : Capture
	// () : �Ű�����
	// -> ��ȯ�� : �����Լ��� ��ȯ��
	// {} : �Լ� ���Ǻ�

	struct Finder
	{
		bool operator()(const int& value)
		{
			if (value > 25)
				return true;
			return false;

		}
		int compare = 25;
	};

	Finder finder;

	int num = 25;
	auto iter = std::find_if(v.begin(), v.end(), [num](const int& value) -> bool
		{
			if (value > num)
				return true;
			return false;
		});

#pragma endregion

	srand(static_cast<unsigned int> (time(nullptr)));
	vector<Vector2> myVec;

	for (int i = 0; i < 20; i++)
	{
		Vector2 temp;
		temp.x = rand() % 21;
		temp.y = rand() % 21;
		myVec.push_back(temp);
	}

	struct FindVector2
	{
		bool operator()(const Vector2& value)
		{
			if (value.x > v.x && value.y < v.y)
			{
				return true;
			}
			return false;
		}
		Vector2 v;
	};
	
	FindVector2 _finder;
	_finder.v.x = 10;
	_finder.v.y = 5;

	Vector2 finderVector;
	finderVector.x = 10;
	finderVector.y = 5;
	auto Vector2Iter = std::find_if(myVec.begin(), myVec.end(), [finderVector](const Vector2& temp) -> bool
	{
			if (temp.x > finderVector.x && temp.y < finderVector.y)
				return true;
			return false;
	});

	// sort
	// Vector2�� ũ�Ⱑ ���� ������ �������ּ���
	std::sort(myVec.begin(), myVec.end());
	std::sort(myVec.begin(), myVec.end(), [](const Vector2& len, const Vector2& len2) -> bool
		{
			int aLength = (len.x * len.x + len.y * len.y);
			int bLength = (len2.x * len2.x + len2.y * len2.y);

			if (aLength > bLength)
				return true;
			return false;
		});

	// x�� 10���� ũ�� y�� 5���� ���� Vector2�� �ִ� �� Ȯ�� ���ּ���
	return 0;
}