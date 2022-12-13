#pragma once
class PaintScene : public Scene
{
public:
	PaintScene();
	virtual ~PaintScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
private:
	vector<HPEN> pens;
	vector<HBRUSH> brushes;

	shared_ptr<CircleCollider> _circle;
	shared_ptr<RectCollider> _rect;

};

