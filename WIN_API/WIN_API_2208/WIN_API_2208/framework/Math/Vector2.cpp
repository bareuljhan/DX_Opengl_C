#include "framework.h"

Vector2::Vector2()
: x(0)
, y(0)
{
}

Vector2::Vector2(float x, float y)
: x(x)
, y(y)
{
}

Vector2::~Vector2()

{
}


Vector2 Vector2::operator+(const Vector2& other) const
{
	Vector2 result;

	result.x = x + other.x;
	result.y = y + other.y;

	return result;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y-other.y);
}

Vector2 Vector2::operator*(const float& value) const
{
	return Vector2(x * value, y * value);
}

bool Vector2::operator<(const Vector2& other) const
{
	if (this->Length() < other.Length())

	return this->Length() < other.Length();
}

bool Vector2::operator>(const Vector2& other) const
{
	if (this->Length() > other.Length())

		return this->Length() > other.Length();
}

bool Vector2::operator==(const Vector2& other) const
{
	if(this->Length() == other.Length())

	return this->Length() == other.Length();
}

bool Vector2::operator+=(const Vector2& other) const
{
	if (this->Length() != other.Length())

	return this->Length() != other.Length();

}

Vector2& Vector2::operator=(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;

	//Vector2 result = *this; // this -> 나 자신인데 나 자신을 가리키는 주소로 가기

	return (*this);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	this->x = x + other.x;
	this->y = y + other.y;

	return (*this);
}

Vector2& Vector2::operator++()
{
	++x;
	++y;

	return (*this);
}

Vector2 Vector2::operator++(int)
{
	Vector2 temp = *this;

	++x;
	++y;

	return temp;
}

float Vector2::Length() const
{
	float temp = x * x + y * y; // <=> powf(x,2) + powf(y,2);

	return sqrt(temp);  // sqrt(powf(x,2) + powf(y,2));
}

float Vector2::Cross(const Vector2& other) const
{
	return 0.0f;
}

Vector2 Vector2::Normal() const
{
	return Vector2();
}
