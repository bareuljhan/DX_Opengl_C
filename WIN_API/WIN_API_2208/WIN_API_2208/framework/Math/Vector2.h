#pragma once
class Vector2
{
public:

	Vector2();
	Vector2(float x, float y);
	~Vector2();


	// a + b : a와 b를 더하고 그 값을 반환..
	Vector2 operator+ (const Vector2& other) const; // 뒤에 const x, y수정하지 않겠다
	Vector2 operator- (const Vector2& other) const;
	Vector2 operator* (const float& value) const;

	// a < b : a가 b보다 작으면  true, 그게 아니면 false 반환
	bool operator< (const Vector2& other) const;
	bool operator> (const Vector2& other) const;
	bool operator== (const Vector2& other) const;
	bool operator+= (const Vector2& other) const;


	// 대입연산자
	// a = b : a에다가 b를 대입하고 a의 원본반환
	// 예외 : 전역함수로 뺄 수 없다.
	Vector2& operator=(const Vector2& other);
	Vector2& operator+=(const Vector2& other);

	// 전위연산자
	// ++a : a에다가 1을 더하고 원본을 반환
	Vector2& operator++();

	// 후위연산자
	// a++ : a을 반환하고 a에다가 1을 더한다.
	Vector2 operator++(int);
	float Length() const;

	float Cross(const Vector2& other) const; // 외적 -> +a.(b) // -c.(a)
	
	Vector2 Normal() const; // 4,0 뽑으면 1,0 이 나온다... 정규화 벡터


public:
	float x;
	float y;
	int mousex;
	int mousey;
};

