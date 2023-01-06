#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>

using namespace std;

// ENCHANT

// +0 집행검

// 강화를 하는데
// + 1
// + 2
// + 3

// N 강을 하고싶다... 이 때 강화를 하는대로 나오는 모든 경우의 수

// 3강을 하고싶다. -> 3C1 + 1
// 1 1 1
// 1 + 2
// 2 + 1
// 3

int NUM = 3;
vector<int> cache = vector<int>(100, -1);

int Enchant(int num)
{
	if (num > NUM)
		return 0;
	if (num == NUM)
		return 1;
	
	// 캐쉬
	int& ref = cache[num];
	if (ref != -1)
		return ref;
	// 구하기
	ref = Enchant(num + 1) + Enchant(num + 2) + Enchant(num + 3);

}


int main()
{
	int result = Enchant(0);

	cout << result << endl;
	return 0;
}