#include "GameScene.h"

void GameScene::Initialize()
{
	LogManager::Log("GameScene_1\n");
}

void GameScene::Update(GameManager* Scene)
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
		Scene->ChangeState(new TitleScene);
		return;
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
