#include "framework.h"
#include "Cannon.h"

Cannon::Cannon()
{
	_body = make_shared<CircleCollider>(Vector2(CENTER_X, CENTER_Y), 30.0f);
	_barrel = make_shared<Barrel>();
	_ball = make_shared<Ball>();
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_body->GetCenter().x += 2.0f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		_body->GetCenter().x -= 2.0f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		_angle += 0.1f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		_angle -= 0.1f;
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		_ball->_isActive = true;
		Vector2 direction = _barrel->GetDirection();
		_ball->Fire(_body->GetCenter(),direction);
	}


	_dir.x = cos(_angle);
	_dir.y = -sin(_angle);

	_barrel->SetStart(_body->GetCenter());
	Vector2 barrelEnd = _dir * _barrelLength;
	_barrel->SetEnd(_body->GetCenter() + barrelEnd);

	_body->Update();
	_barrel->Update();
	_ball->Update();

}

void Cannon::Render(HDC hdc)
{
	_barrel->Render(hdc);
	_body->Render(hdc);
	_ball->Render(hdc);
}
