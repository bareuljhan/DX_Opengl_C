#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <array>

using namespace std;

// 레이드
// 0. World 2로 해서 만들기 전에 있던거에
// 1. Boss 구현 - Monster를 상속받는다, Goblin을 상속받아도 된다.
// 2. Boss 한마리, 플레이어 10명이서 싸우기
// - Boss는 AggroSystem을 이용하여 어그로 수치가 제일 높은 3 ~ 4명 정도를 공격
// Player* damage
// 0x1213.. 플레이어 포인터가 500
// 0x1210.. 300
// 0x1111.. 700
// 0x1112.. 1000
// 세마리 때려야 한다면 정렬 해서 세마리 때리기
// 만약 죽었으면 삭제 혹은 아래로 내리기

// Modern C++
// C++ 11 부터를 말한다. ( 버전체크 -> C++ reference )

// auto
// -> 반드시 초기화가 필요하다.
// -> 가독성이 떨어진다.

// 중괄호 초기화
// -> 배열과 일반 변수 초기화 하는 방법을 동일하게

// 범위기반 for문
// -> 많이 쓴다.

// final override
// friend

// using
// enum class
// -> enum은 이름이 겹치면 컴파일에러가 난다.
// => 이름이 겹쳐야 하는 상황이면 enum class를 써야한다.
// => 취향차이

// 람다

// 이동 shift 개념

// 스마트 포인터

class Player
{
public:
    friend class Pet; // -> Pet은 이제 Player 의 private 영역의 멤버함수, 멤버변수를 쓸 수 있게 된다.

    Player(int a, int b)
       
    {
        cout << "타입변환 생성자" << endl;
    }

    virtual void Attack() { cout << "Attack" << endl; };

private:
    int _hp;
};

class Knight : public Player
{
public:
    Knight()
    :Player(10, 5)
    {

    }
    virtual void Attack() final override{ cout << "Knight Attack~" << endl; }; // 이후 해당 가상함수 사용 불가능
};

class Pet
{
public:
    void Set(Player* p) { this->p = p; }
    void Act()
    {
        p->Attack();
        p->_hp;
    }
private:
    Player* p;
};

enum class ClassType
{
    NONE,
    KNIGHT,
    MAGE,
    ARCHER
};

enum class PetType
{
    NONE,
    KNIGHT_PET,
    MAGE_PET,
    ARCHER_PET
};

int main()
{
    unordered_map<int, Knight*> umap;
    //int arr1[10];
    //array<int, 10> t;

    unordered_map<int, int> uMap;
    uMap[0] = 1;
    uMap[1] = 2;
    uMap[2] = 3;

    // auto
    // 자료형 추론
    auto iter = uMap.begin(); // <=> unordered_map<int, int>::iterator -> 선언만 할 수는 없다. auto iter; (x)
    for (iter; iter != uMap.end(); ++iter)
    {
        cout << iter->first << endl;
    }

    // 중괄호 초기화
    Player p = { 1,5 };
    int arr[5] = { 1,2,3,4,5 };

    // 범위기반 for문
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    for (const int& value : v) // <=> (const auto& value : v)
    {
        cout << value << endl;
    }

    for (const pair<int, int>& p : uMap) // <=> (const auto& p : uMap) 키가 같을때 체인잉 리스트로 바뀜
    {
        cout << p.first << endl;
    }

    // using
    typedef unsigned int UINT2;
    using UINT = unsigned int; // -> template 호환 가능
    UINT t;

    // enum class
    ClassType type = ClassType::NONE;
    int a = static_cast<int>(type);
    
    return 0;
}