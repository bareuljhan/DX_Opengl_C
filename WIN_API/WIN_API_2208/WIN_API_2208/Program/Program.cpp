#include "framework.h"
#include "Program.h"


#include "../Scene/PaintScene.h"
#include "../Scene/CollisionScene.h"

Program::Program()
{
	_sceneTable["Paint"] = make_shared<PaintScene>();
	_sceneTable["Collision"] = make_shared<CollisionScene>();

	_curScene = _sceneTable["Collision"];
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
