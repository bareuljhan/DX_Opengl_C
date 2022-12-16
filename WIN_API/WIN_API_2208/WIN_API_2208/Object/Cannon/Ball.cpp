#include "framework.h"
#include "Ball.h"

Ball::Ball()
{
	_circle = make_shared<CircleCollider>(Vector2(0,0),5);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (_isActive == false)
		return;
	_circle->GetCenter() += _dir * _speed;

	_circle->Update();
}

void Ball::Render(HDC hdc)
{
	if (_isActive == false)
		return;

	_circle->Render(hdc);
}

void Ball::Fire(Vector2 pos, Vector2 dir)
{
	_circle->GetCenter() = pos;
	_dir = dir.NormalVector2();
}
