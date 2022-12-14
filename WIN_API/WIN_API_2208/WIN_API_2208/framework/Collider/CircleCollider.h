#pragma once
class CircleCollider : public
{
public:
	CircleCollider();
	CircleCollider(Vector2 center, float radius);
	~CircleCollider();

	void Update();
	void Render(HDC hdc);

	Vector2& GetCenter() { return center; }
	float& GetRadius() { return radius; }

	void SetRed() { _curPen = _pens[0]; }
	void SetGreen() { _curPen = _pens[1]; }

	bool IsCollision(const Vector2& pos);
	bool IsCollision(const shared_ptr<CircleCollider> circle);
	bool IsCollision(const shared_ptr<class RectCollider> rect);

private:
	vector<HPEN> _pens;

	HPEN _curPen;

	Vector2 center;
	float radius;
};

