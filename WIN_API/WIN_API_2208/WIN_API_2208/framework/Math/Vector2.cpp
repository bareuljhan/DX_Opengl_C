#include "framework.h"
#include "Vector2.h"

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

Vector2::Vector2(int x, int y)
	:x((float)x)
	,y((float)y)
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
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(const float& value) const
{
	return Vector2(x * value, y * value);
}

bool Vector2::operator<(const Vector2& other) const
{
	return this->Length() < other.Length();
}

bool Vector2::operator>(const Vector2& other) const
{
	return this->Length() > other.Length();
}

bool Vector2::operator==(const Vector2& other) const
{
	if (x == other.x && y == other.y)
		return true;
	return false;
}

bool Vector2::operator!=(const Vector2& other) const
{
	return !this->operator==(other);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	this->x = this->x + other.x;
	this->y = this->y + other.y;

	return (*this);
}

Vector2& Vector2::operator=(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;

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
	return sqrt(powf(x, 2) + powf(y, 2));
}

float Vector2::Cross(const Vector2& other)
{
	return x * other.y - y * other.x;
}

float Vector2::Dot(const Vector2& other) const
{
	return (other.x * x + other.y * y);
}
bool Vector2::IsBetween(const Vector2& a, const Vector2& b)
{
	float z1 = this->Cross(a);
	float z2 = this->Cross(b);

	if (z1 * z2 < 0)
		return true;

	return false;
}

Vector2 Vector2::NormalVector2()
{
	Vector2 temp;
	temp.x = x / Length();
	temp.y = y / Length();

	return temp;
}

void Vector2::Normalize()
{
	float length = Length();

	x = x / length;
	y = y / length;
}

float Vector2::Manhattan(const Vector2& other) const
{
	float mx = abs(other.x - x);
	float my = abs(other.y - y);
	return mx + my;
}
