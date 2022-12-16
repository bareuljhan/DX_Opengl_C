#pragma once
class Collider
{
public:
	enum class Type
	{
		NONE,
		CIRCLE,
		RECT
	};

	Collider();
	virtual ~Collider();

	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

	Vector2& GetCenter() { return center; }

	void SetRed() { _curPen = _pens[0]; }
	void SetGreen() { _curPen = _pens[1]; }

	bool IsCollision(shared_ptr<Collider> col);
	virtual bool IsCollision(const Vector2& pos) abstract;
	virtual bool IsCollision(const shared_ptr<class CircleCollider> circle) abstract;
	virtual bool IsCollision(const shared_ptr<class RectCollider> rect) abstract;


	Type GetType() { return _type; }
	
	bool _isActive = true;
protected:
	Type _type;
	vector<HPEN> _pens;
	HPEN _curPen;

	Vector2 center;
};

