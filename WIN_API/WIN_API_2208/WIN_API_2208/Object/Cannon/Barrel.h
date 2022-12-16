#pragma once
class Barrel
{
public:
	Barrel();
	~Barrel();

	void Update();
	void Render(HDC hdc);

	void SetStart(Vector2 pos) { _line->_startPos = pos; }
	void SetEnd(Vector2 pos) { _line->_endPos = pos; }

	Vector2 GetDirection() { return _line->_endPos - _line->_startPos; }
private:
	shared_ptr<Line> _line;

};

