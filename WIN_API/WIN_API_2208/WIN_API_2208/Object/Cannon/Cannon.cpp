#include "framework.h"
#include "Cannon.h"

Cannon::Cannon()
{
	_body = make_shared<CircleCollider>(Vector2(CENTER_X, CENTER_Y), 30.0f);
	_barrel = make_shared<Barrel>();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Ball> ball = make_shared<Ball>();
		ball->_isActive = false;
		_balls.push_back(ball);
	}
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
	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		auto ball = std::find_if(_balls.begin(), _balls.end(), [](const shared_ptr<Ball>& ball)->bool
			{
				if (!ball->_isActive)
					return true;
				return false;
			});
		Vector2 direction = _barrel->GetDirection();
		if (ball != _balls.end())
		{
			(*ball)->_isActive = true;
			Vector2 startPos = _barrel->GetEndPos();
			(*ball)->Fire(startPos,direction);
		}
	}

	_dir.x = cos(_angle);
	_dir.y = -sin(_angle);

	_barrel->SetStart(_body->GetCenter());
	Vector2 barrelEnd = _dir * _barrelLength;
	_barrel->SetEnd(_body->GetCenter() + barrelEnd);

	_body->Update();
	_barrel->Update();
	for(auto ball : _balls)
		ball->Update();

}

void Cannon::Render(HDC hdc)
{
	_barrel->Render(hdc);
	_body->Render(hdc);
	for (auto ball : _balls)
		ball->Render(hdc);
}
