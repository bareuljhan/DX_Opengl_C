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

	if (_delay >= 30.0f)
	{
		_isActive = false;
		_delay = 0.0f;
	}
	 
	_delay += 0.1f;
	_circle->GetCenter() += _dir * _speed;

	if (_circle->GetCenter().y < 0 || _circle->GetCenter().y > WIN_HEIGHT)
		_dir.y *= -1;
	if (_circle->GetCenter().x < 0 || _circle->GetCenter().x > WIN_WIDTH)
		_dir.x *= -1;
	//_dir.y += GRAVITY * 0.01f;

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