#include "TitleScene.h"

void TitleScene::Initialize()
{
	LogManager::Log("TitleScene");
	view.Initialize();
}

void TitleScene::Update(GameManager* Scene)
{
	Scene;
	ImGui::Begin("Title");

	ImGui::End();

	view.UpdateMatrix();
}

void TitleScene::Back2dSpriteDraw()
{

}

void TitleScene::Object3dDraw()
{
}

void TitleScene::Flont2dSpriteDraw()
{
}
