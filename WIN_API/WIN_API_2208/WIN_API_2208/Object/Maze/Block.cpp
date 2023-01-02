#include "framework.h"
#include "Block.h"

Block::Block()
{
	_rect = make_shared<RectCollider>(Vector2(CENTER_X, CENTER_Y), Vector2(14, 14));

	HBRUSH white = CreateSolidBrush(RGB(
		5, 255, 255));
	HBRUSH green = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH red = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH yellow = CreateSolidBrush(RGB(0xFF, 0xFF, 0));
	HBRUSH cyan = CreateSolidBrush(RGB(0, 0xFF, 0xFF));
	HBRUSH purple = CreateSolidBrush(RGB(0x80, 0x00, 0x80));
	HBRUSH grey = CreateSolidBrush(RGB(150, 150, 150));
	HBRUSH blue = CreateSolidBrush(RGB(50, 50, 200));

	_brushes.push_back(white);
	_brushes.push_back(green);
	_brushes.push_back(red);
	_brushes.push_back(yellow);
	_brushes.push_back(cyan);
	_brushes.push_back(purple);
	_brushes.push_back(grey);
	_brushes.push_back(blue);
}

Block::~Block()
{
	for (auto& brush : _brushes)
		DeleteObject(brush);
}

void Block::Update()
{
	_rect->Update();
}

void Block::Render(HDC hdc)
{
	SelectObject(hdc, _brushes[static_cast<UINT>(_type)]);
	switch (_type)
	{
	case Block::Type::NONE:
		break;
	case Block::Type::ABLE:
		_rect->SetGreen();
		break;
	case Block::Type::DISABLE:
		_rect->SetRed();
		break;
	case Block::Type::START:
		_rect->SetRed();
		break;
	case Block::Type::END:
		_rect->SetRed();
		break;	
	default:
		break;
	}
	_rect->Render(hdc);
}
