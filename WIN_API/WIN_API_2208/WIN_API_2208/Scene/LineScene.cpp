#include "framework.h"
#include "LineScene.h"

LineScene::LineScene()
{
	_line1 = make_shared<Line>();
	_line1->_startPos = Vector2(CENTER_X, CENTER_Y);
	_line2 = make_shared<Line>();
	_line2->_startPos = { 0,0 };
	_line2->_endPos = { 800, 500 };
}

LineScene::~LineScene()
{
}

void LineScene::Update()
{
	_line1->_endPos = mousePos;
	_line1->Update();
	_line2->Update();
	
	//if (_line1->IsCollision(_line2))
	//{
	//	_line1->SetRed();
	//	_line2->SetRed();
	//}
	//else
	//{
	//	_line1->SetGreen();
	//	_line2->SetGreen();
	//}
}

void LineScene::Render(HDC hdc)
{
	_line1->Render(hdc);
	_line2->Render(hdc);
}
