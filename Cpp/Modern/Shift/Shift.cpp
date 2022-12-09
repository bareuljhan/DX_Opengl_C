#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <array>

using namespace std;

// 이동(Shift, move)
// 비트연산자... <<, >>

// C++ 11
// 이전 버전-> 이동 개념이 없다.. 복사하고 새로 생성하고 전에 있던 데이터를 삭제.
// 그러나 11이후 이동개념이 생겨서 복사, 생성이 아니고 바로 데이터 이사 -> 집이 같은 형태일 때 껍데기만 남기고 내용물은 이사

class Pet
{
};

class Player
{
public:
	Player() { _pet = new Pet(); }
	~Player()
	{
		if (_pet != nullptr)
			delete _pet;
	}

	// 이거 다시 공부.... 깊은 복사
	Player(const Player& other)
	{
		_pet = new Pet(*other._pet);
	}

	// 이동생성자 -> 이사 생성자... Player는 생성되는게 아니라 원래 있던 애의 pet을 가져옴
	Player(Player&& other) noexcept
	{
		_pet = other._pet;

		other._pet = nullptr;
	}

	// 복사대입연산자
	Player& operator=(const Player& other)
	{
		_pet = new Pet(*other._pet);
		return (*this);
	}

	// 이동대입연산자
	Player& operator=(Player&& other)
	{
		_pet = other._pet;
		other._pet = nullptr;
		return (*this);
	}
private:
	
public:
	Pet* _pet;
};

void MovePet(Player& player, Player&& player2)
{
	delete player._pet;
	player._pet = nullptr;

	player._pet = player2._pet;
	player2._pet = nullptr;
}

void PrintPlayerValue(Player player)
{
	// 장점
	// -player 바꿔도 원본이 안 바뀜
	
	// 단점
	// - player라는 매개변수가 복사된다.
}

void PrintPlayerAddress(Player* player)
{
	// 장점
	// - 원본을 갖고 온다.
	// - 포인터를 복사해서 4 or 8바이트만 할당된다.

	// 단점
	// 예외처리, 메모리 오염이 일어날 수 있다.
	// - 원본을 수정할 수 있다.
}

void PrintPlayerRef(Player& player)
{
	// 장점
	// - 원본을 갖고 온다.
	// - 포인터를 복사해서 4 or 8바이트만 할당된다.
	
	// 단점
	// - nullptr이 올 수 없다.
	// - 값 전달이랑 헷갈릴 수 있다.
	// - 원본을 수정할 수 있다.
}

void PrintPlayerConstRef(const Player& player)
{
	// 장점
	// - 원본을 갖고 온다.
	// - 포인터를 복사해서 4 or 8바이트만 할당된다.

	// 단점
	// - 원본을 수정할 수 없다.
}


void PrintPlayerRRef(Player&& player)
{

	// 힌트
	// 오른값 참조로 받은 매개변수는 일시적인 객체이다.
	// 수정권한도 주고, 지역 안에서 원본을 마음대로 바꿀 수 있다.
	// --- 임시객체라고 생각하고 마음대로 바꾸어도 상관없다.

}


int main()
{
	// && : 오른값 참조 (r_value의 원본을 갖고온다?)
	// l_value : 수정이 가능한 변수 - 대표 : 참조
	// r_value : l_value가 아닌 변수 - 대표 : 상수

	const int aInt = 5; // aInt -> l_value
	int bInt = 10;
	int cInt = bInt; // 둘다 l_value

	// vector<int>() <=> 5 비슷하다 둘이
	// Player(); => 임시객체 ( 이 줄이 끝나면 사라지는 객체 )
	Player p1;
	Player p2(static_cast<Player&&>(Player()));
	Player p3;
	p3 = std::move(p1);;

	unique_ptr<Player> u_p = make_unique<Player>(); // ... 포인터인데 딱 하나만 존재
	unique_ptr<Player> u_p2 = std::move(u_p);

   return 0;
}