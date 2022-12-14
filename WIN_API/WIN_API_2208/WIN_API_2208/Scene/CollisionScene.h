#pragma once
class CollisionScene : public Scene
{
public:
	CollisionScene();
	virtual ~CollisionScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
private:
	shared_ptr<CircleCollider> _circle1;
	shared_ptr<CircleCollider> _circle2;

	shared_ptr<RectCollider> _rect1;
	shared_ptr<RectCollider> _rect2;
};

