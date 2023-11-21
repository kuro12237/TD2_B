#include "TitleScene.h"

void TitleScene::Initialize()
{

	LogManager::Log(SceneName+"\n");
	model_ = make_unique<Model>();
	uint32_t tex = TextureManager::LoadTexture("Resources/uvChecker.png");

	model_->SetTexHandle(tex);
	model_->Initialize(new ModelSphereState);
	worldTransform_.Initialize();


	view.Initialize();

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

	if (Input::GetInstance()->PushKeyPressed(DIK_SPACE))
	{
		Scene->ChangeState(new SlectStage);
		return;
	}
		


	worldTransform_.UpdateMatrix();

	view.UpdateMatrix();
}

void TitleScene::Back2dSpriteDraw()
{

}

void TitleScene::Object3dDraw()
{
	model_->Draw(worldTransform_, view);
}

void TitleScene::Flont2dSpriteDraw()
{
	
}
