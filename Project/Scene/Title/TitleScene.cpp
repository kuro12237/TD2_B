#include "TitleScene.h"

void TitleScene::Initialize()
{
	DebugCamera* Camera;
	Camera= new DebugCamera();
	Camera->Initialize();
	DebugTools::addCommand(Camera, "f");

	LogManager::Log(SceneName+"\n");
	model_ = make_unique<Model>();
	uint32_t tex = TextureManager::LoadTexture("Resources/uvChecker.png");

	model_->SetTexHandle(tex);
	model_->Initialize(new ModelSphereState);
	worldTransform_.Initialize();


	view.Initialize();
	view.translation_ = { 0,3,-10 };
	view.UpdateMatrix();
}

void TitleScene::Update(GameManager* Scene)
{
	if (ImGui::TreeNode("Scene"))
	{
		bool flag = false;
		if (ImGui::Checkbox("changeSecne", &flag))
		{
			SceneChange::ChangeStart();
		}
		ImGui::TreePop();
	}
	
	if (SceneChange::GetScenChangeFlag())
	{
		Scene->ChangeState(new GameScene);
		return;
	}

	DebugTools::UpdateExecute(0);
	worldTransform_.UpdateMatrix();

	SkyBox::Update();
	Ground::Update();
	TruckManager::Update();

	view.UpdateMatrix();
	view = DebugTools::ConvertViewProjection(view);
}

void TitleScene::Back2dSpriteDraw()
{

}

void TitleScene::Object3dDraw()
{
	DebugTools::DrawExecute(0);
	//model_->Draw(worldTransform_, view);
	TruckManager::Draw(view);

	SkyBox::Draw(view);
	Ground::Draw(view);
}

void TitleScene::Flont2dSpriteDraw()
{
	
}
