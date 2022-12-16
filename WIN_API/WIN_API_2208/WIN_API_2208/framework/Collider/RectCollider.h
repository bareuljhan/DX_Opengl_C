#pragma once
class RectCollider : public Collider
{

public:
	RectCollider();
	RectCollider(Vector2 center, Vector2 size);
	~RectCollider();


	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	Vector2& GetSize() { return size; }

	float Left() { return center.x - size.x * 0.5f; }
	float Top() { return center.y - size.y * 0.5f; }
	float Right() { return center.x + size.x * 0.5f; }
	float Bottom() { return center.y + size.y * 0.5f; }



	// AABB 충돌
	// -> 회전하지 않는 사각형의 충돌
	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(const shared_ptr<RectCollider> rect) override;
	virtual bool IsCollision(const shared_ptr<CircleCollider> circle) override;

	Vector2 LeftTop() { return Vector2(center.x - size.x * 0.5f, center.y - size.y * 0.5f); }
	Vector2 RightTop() { return Vector2(center.x + size.x * 0.5f, center.y - size.y * 0.5f); }
	Vector2 LeftBottom() { return Vector2(center.x - size.x * 0.5f, center.y + size.y * 0.5f); }
	Vector2 RightBottom() { return Vector2(center.x + size.x * 0.5f, center.y + size.y * 0.5f); }
private:

	Vector2 size;
};

