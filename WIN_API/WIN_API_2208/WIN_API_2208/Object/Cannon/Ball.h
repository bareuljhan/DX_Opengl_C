#pragma once
class Ball
{
public:
	Ball();
	~Ball();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector2 pos, Vector2 dir);

	bool _isActive = false;
private:
	shared_ptr<CircleCollider> _circle;

	Vector2 _dir = { 0, 0 };
	float _speed = 5.0f;

	float _delay = 0.0f;
};

