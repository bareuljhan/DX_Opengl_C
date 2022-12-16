#include "framework.h"
#include "Barrel.h"

Barrel::Barrel()
{
	_line = make_shared<Line>();
}

Barrel::~Barrel()
{
}

void Barrel::Update()
{
	_line->Update();
}

void Barrel::Render(HDC hdc)
{
	_line->Render(hdc);
}
