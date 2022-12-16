#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector2 center, float radius)
:Collider()
,radius(radius)
{
	this->center = center;
	_type = Collider::Type::CIRCLE;
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	if (_isActive == false)
		return;
}

void CircleCollider::Render(HDC hdc)
{
	if (_isActive == false)
		return;
	SelectObject(hdc, _curPen);
	float left = center.x - radius;
	float top = center.y - radius;
	float right = center.x + radius;
	float bottom = center.y + radius;
	Ellipse(hdc, left, top, right, bottom);
}

bool CircleCollider::IsCollision(const Vector2& pos)
{
	if (_isActive == false)
		return false;
	Vector2 centerToPos = pos - center;
	float length = centerToPos.Length();

	return length <= radius;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> circle)
{
	Vector2 centerToCenter = circle->center - center;
	float length = centerToCenter.Length();

	return (radius + circle->radius) >= length;
}

bool CircleCollider::IsCollision(shared_ptr<class RectCollider> rect)
{
	if (center.x <= rect->Right() && center.x >= rect->Left())
		if (center.y <= rect->Right() + radius && center.y >= rect->Top() - radius)
			return true;

	if (center.x <= rect->Right() + radius && center.x >= rect->Left() - radius)
		if (center.y <= rect->Right() && center.y >= rect->Top())
			return true;
	
	if (this->IsCollision(rect->LeftTop()) || this->IsCollision(rect->RightTop()) || 
		this->IsCollision(rect->LeftBottom()) || this->IsCollision(rect->RightBottom()))
		return true;
	return false;
}