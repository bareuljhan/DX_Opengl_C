#pragma once
class Vector2
{
public:

	Vector2();
	Vector2(float x, float y);
	~Vector2();


	// a + b : a�� b�� ���ϰ� �� ���� ��ȯ..
	Vector2 operator+ (const Vector2& other) const; // �ڿ� const x, y�������� �ʰڴ�
	Vector2 operator- (const Vector2& other) const;
	Vector2 operator* (const float& value) const;

	// a < b : a�� b���� ������  true, �װ� �ƴϸ� false ��ȯ
	bool operator< (const Vector2& other) const;
	bool operator> (const Vector2& other) const;
	bool operator== (const Vector2& other) const;
	bool operator+= (const Vector2& other) const;


	// ���Կ�����
	// a = b : a���ٰ� b�� �����ϰ� a�� ������ȯ
	// ���� : �����Լ��� �� �� ����.
	Vector2& operator=(const Vector2& other);
	Vector2& operator+=(const Vector2& other);

	// ����������
	// ++a : a���ٰ� 1�� ���ϰ� ������ ��ȯ
	Vector2& operator++();

	// ����������
	// a++ : a�� ��ȯ�ϰ� a���ٰ� 1�� ���Ѵ�.
	Vector2 operator++(int);
	float Length() const;

	float Cross(const Vector2& other) const; // ���� -> +a.(b) // -c.(a)
	
	Vector2 Normal() const; // 4,0 ������ 1,0 �� ���´�... ����ȭ ����


public:
	float x;
	float y;
	int mousex;
	int mousey;
};

