#pragma once
class LineScene : public Scene
{
public:
	struct Result
	{
		Vector2 contact;
		bool isCollision;
	};
	LineScene();
	virtual ~LineScene();
private:


	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	shared_ptr<Line> _line1;
	shared_ptr<Line> _line2;
};

