#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider()
:Collider()
{
	size = Vector2(0, 0);
}

RectCollider::RectCollider(Vector2 center, Vector2 size)
:size(size)
{
    this->center = center;
    _type = Collider::Type::RECT;
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    if (_isActive == false)
        return;
}

void RectCollider::Render(HDC hdc)
{
    if (_isActive == false)
        return;
    SelectObject(hdc, _curPen);
	Rectangle(hdc, Left(), Top(), Right(), Bottom());
}

bool RectCollider::IsCollision(const Vector2& pos)
{
    if (_isActive == false)
        return false;
    if (pos.x <= Right() && pos.x >= Left())
    {
        if (pos.y <= Bottom() && pos.y >= Top())
            return true;
    }
    return false;
}

bool RectCollider::IsCollision(const shared_ptr<RectCollider> rect)
{
    if (Right() >= rect->Left() && Left() <= rect->Right())
    {
        if (Bottom() >= rect->Top() && Top() <= rect->Bottom())
            return true;
    }
    return false;
}

bool RectCollider::IsCollision(const shared_ptr<CircleCollider> circle)
{
    Vector2 center = circle->GetCenter();
    float radius = circle->GetRadius();

    if (center.x <= Right() && center.x >= Left())
        if (center.y <= Right() + radius && center.y >= Top() - radius)
            return true;

    if (center.x <= Right() + radius && center.x >= Left() - radius)
        if (center.y <= Right() && center.y >= Top())
            return true;

    if (circle->IsCollision(LeftTop()) || circle->IsCollision(RightTop()) ||
        circle->IsCollision(LeftBottom()) || circle->IsCollision(RightBottom()))
        return true;
}