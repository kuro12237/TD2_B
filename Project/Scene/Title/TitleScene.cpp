#include "TitleScene.h"

void TitleScene::Initialize()
{

	LogManager::Log(SceneName+"\n");
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
	}

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
