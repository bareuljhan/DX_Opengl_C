#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>

using namespace std;

// Dynamic Programming
// 컴퓨터 공학 : 동적 -> 실행 시간에 할 수 있는 무언가
// => 이름이 멋있어서

// f(0) = 1
// f(1) = 1
// f(n) = f(n-1) + f(n-2)

int cache[100];

int Fibonacci(int n, int& count)
{
	// 기저사항
	if (n == 0 || n == 1)
		return 1;
	if (n == 2)
		count++;

	// 캐시
	if (cache[n] != -1)
		return cache[n];

	// 구하기
	cache[n] = Fibonacci(n - 1, count) + Fibonacci(n - 2, count);
	return cache[n];	
}


int main()
{
	__int64 start = GetTickCount64();
	int count = 0;

	for (int i = 0; i < 100; i++)
	{
		cache[i] = -1;
	}

	cout << Fibonacci(99, count) << endl;
	cout << count << endl;
	__int64 end = GetTickCount64();

	cout << end - start << "ms" << endl;
	return 0;
}