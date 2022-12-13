#include "framework.h"
#include "Program.h"


#include "../Scene/PaintScene.h"
Program::Program()
{
	_sceneTable["PaintScene"] = make_shared<PaintScene>();
	_curScene = _sceneTable["PaintScene"];
}

Program::~Program()
{

}

void Program::Update()
{
	_curScene->Update();
}

void Program::Render(HDC hdc)
{
	_curScene->Render(hdc);
}
