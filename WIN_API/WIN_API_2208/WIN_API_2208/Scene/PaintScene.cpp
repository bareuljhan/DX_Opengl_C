#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{


    _rect = make_shared<RectCollider>(Vector2(CENTER_X, CENTER_Y), Vector2(100, 80));
    _circle = make_shared<CircleCollider>(Vector2(CENTER_X + 100, CENTER_Y), 30);

    _rect->SetRed();
}

PaintScene::~PaintScene()
{
}

void PaintScene::Update()
{
    //_rect->GetCenter().x += 0.1f;

    _rect->Update();
    _circle->Update();
}

void PaintScene::Render(HDC hdc)
{

    // Brush �� ����
    //SelectObject(hdc, brushes[0]);

    // �簢�� �׸��� -> ������ ���� �׷����°� �޶���
    //Rectangle(hdc, 0, 0, 500, 500);
    _rect->Render(hdc);
    _circle->Render(hdc);

    // ���׸���
    //Ellipse(hdc, mousePos.x - 25, mousePos.y - 25, mousePos.x + 25, mousePos.y + 25);
    
    // �� �׸���
    //MoveToEx(hdc, 0, 0, nullptr);
    //LineTo(hdc, mousePos.x, mousePos.y
    // 
}
