#include "framework.h"
#include "Program.h"

#include "../Scene/PaintScene.h"
#include "../Scene/CannonScene.h"
#include "../Scene/CollisionScene.h"
#include "../Scene/LineScene.h"

Program::Program()
{
	_sceneTable["Paint"] = make_shared<PaintScene>();
	_sceneTable["Collision"] = make_shared<CollisionScene>();
	_sceneTable["Line"] = make_shared<LineScene>();
	_sceneTable["Cannon"] = make_shared<CannonScene>();

	_curScene = _sceneTable["Cannon"];
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
