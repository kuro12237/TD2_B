#include "GameScene.h"

void GameScene::Initialize()
{
	LogManager::Log("GameScene_1\n");
}

void GameScene::Update(GameManager* Scene)
{

	if (SceneChange::GetScenChangeFlag())
	{
		Scene->ChangeState(new TitleScene);
	}

	if (ImGui::TreeNode("Scene"))
	{
		bool flag = false;
		if (ImGui::Checkbox("changeSecne", &flag))
		{
			SceneChange::SetIsStart(flag);
		}
		ImGui::TreePop();
	}


}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
}

void GameScene::Flont2dSpriteDraw()
{
}
