#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider()
{
	center = Vector2(0, 0);
	size = Vector2(0, 0);

    {
        _pens.reserve(3);
        HPEN red = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
        HPEN green = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
        HPEN blue = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
        _pens.push_back(red);
        _pens.push_back(green);
        _pens.push_back(blue);
    }
}

RectCollider::RectCollider(Vector2 center, Vector2 size)
:center(center)
,size(size)
{
    {
        _pens.reserve(3);
        HPEN red = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
        HPEN green = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
        HPEN blue = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
        _pens.push_back(red);
        _pens.push_back(green);
        _pens.push_back(blue);

        _curPen = _pens[1];
    }
}

RectCollider::~RectCollider()
{
    for (auto& pen : _pens)
        DeleteObject(pen);
}

void RectCollider::Update()
{
}

void RectCollider::Render(HDC hdc)
{
    SelectObject(hdc, _curPen);
	Rectangle(hdc, Left(), Top(), Right(), Bottom());
}

bool RectCollider::IsCollision(const Vector2& pos)
{
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

}