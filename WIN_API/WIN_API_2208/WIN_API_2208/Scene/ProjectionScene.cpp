#include "framework.h"
#include "ProjectionScene.h"

ProjectionScene::ProjectionScene()
{
	_line1 = make_shared<Line>();
	_line1->_startPos = Vector2(100, 100);


	_line2 = make_shared<Line>();
	_line2->_startPos = Vector2(100, 600);
	_line2->_endPos = Vector2(WIN_WIDTH, 300);

	_projection = make_shared<Line>();
	_projection->_startPos = Vector2(100, 500);
	_projection->_endPos = Vector2(101, 550);

}

ProjectionScene::~ProjectionScene()
{
}

void ProjectionScene::Update()
{
	// 내적할때 길이가 1인 벡터에다가 내적하면 그림자가 나온다.
	_line1->_endPos = mousePos;
	Vector2 line1Vec = _line1->_endPos - _line1->_startPos;
	Vector2 line2Vec = _line2->_endPos - _line2->_startPos;
	line2Vec.Normalize();
	float length = line2Vec.Length();
	float dot = line1Vec.Dot(line2Vec);

	_projection->_endPos = _projection->_startPos + line2Vec * dot;

	//Vector2 b =_line1->_endPos - _line2->_startPos;
	//float px = b.Dot(_line2->_endPos - _line2->_startPos);
	//float py = b.Dot(_line1->_endPos - _line2->_startPos);
	//_projection->_startPos = Vector2(px, py);

	_line1->Update();
	_line2->Update();
	_projection->Update();
}

void ProjectionScene::Render(HDC hdc)
{
	_line1->Render(hdc);
	_line2->Render(hdc);
	_projection->Render(hdc);
}