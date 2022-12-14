#pragma once
class RectCollider
{

public:
	RectCollider();
	RectCollider(Vector2 center, Vector2 size);
	~RectCollider();

	void Update();
	void Render(HDC hdc);

	Vector2& GetCenter() { return center; }
	Vector2& GetSize() { return size; }

	float Left() { return center.x - size.x * 0.5f; }
	float Top() { return center.y - size.y * 0.5f; }
	float Right() { return center.x + size.x * 0.5f; }
	float Bottom() { return center.y + size.y * 0.5f; }

	void SetRed() { _curPen = _pens[0]; }
	void SetGreen() { _curPen = _pens[1]; }

	// AABB 충돌
	// -> 회전하지 않는 사각형의 충돌
	bool IsCollision(const Vector2& pos);
	bool IsCollision(const shared_ptr<RectCollider> rect);
	bool IsCollision(const shared_ptr<CircleCollider> circle);

private:
	vector<HPEN> _pens;

	HPEN _curPen;

	Vector2 center;
	Vector2 size;
};

