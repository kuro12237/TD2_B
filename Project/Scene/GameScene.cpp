#include "GameScene.h"

void GameScene::Initialize()
{
	LogManager::Log("GameScene_1\n");
	MapManager::Initialize();
	viewProjection_.Initialize();
	viewProjection_.translation_.x = 7;
	viewProjection_.translation_.y = 7;
	viewProjection_.translation_.z = -39;
	viewProjection_.UpdateMatrix();
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

	if (ImGui::TreeNode("Camera"))
	{
		ImGui::DragFloat3("CameraTranslate", &viewProjection_.translation_.x);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("MapData"))
	{
		bool flag = false;
		ImGui::Checkbox("MapStage1",&flag );
		if (flag)
		{
			MapManager::SetSelectMap(1);
		}

		bool flag2 = false;
		ImGui::Checkbox("MapStage2", &flag2);
		if (flag2)
		{
			MapManager::SetSelectMap(2);
		}

		bool flag3 = false;
		ImGui::Checkbox("MapStage3", &flag3);
		if (flag3)
		{
			MapManager::SetSelectMap(3);
		}
		bool flag4 = false;
		ImGui::Checkbox("MapStage4", &flag4);
		if (flag4)
		{
			MapManager::SetSelectMap(4);
		}
		bool flag5 = false;
		ImGui::Checkbox("MapStage5", &flag5);
		if (flag5)
		{
			MapManager::SetSelectMap(5);
		}
		bool flag6 = false;
		ImGui::Checkbox("MapStage6", &flag6);
		if (flag6)
		{
			MapManager::SetSelectMap(6);
		}
		bool flag7 = false;
		ImGui::Checkbox("MapStage7", &flag7);
		if (flag7)
		{
			MapManager::SetSelectMap(7);
		}
		bool flag8 = false;
		ImGui::Checkbox("MapStage8", &flag8);
		if (flag8)
		{
			MapManager::SetSelectMap(8);
		}
		bool flag9 = false;
		ImGui::Checkbox("MapStage9", &flag9);
		if (flag9)
		{
			MapManager::SetSelectMap(9);
		}
		bool flag10 = false;
		ImGui::Checkbox("MapStage10", &flag10);
		if (flag10)
		{
			MapManager::SetSelectMap(10);
		}
		ImGui::TreePop();
	}

	if (SceneChange::GetScenChangeFlag())
	{
		Scene->ChangeState(new TitleScene);
		return;
	}

	MapManager::Update();

	viewProjection_.UpdateMatrix();
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	MapManager::GetInstance()->Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}
