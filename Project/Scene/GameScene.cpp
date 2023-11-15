#include "GameScene.h"

void GameScene::Initialize()
{
	DebugCamera* debugCamera = new DebugCamera();
	debugCamera->Initialize();
	DebugTools::addCommand(debugCamera,"d");

	LogManager::Log("GameScene_1\n");
	MapManager::Initialize();
	viewProjection_.Initialize();
	viewProjection_.translation_.x = 7;
	viewProjection_.translation_.y = 7;
	viewProjection_.translation_.z = -39;
	viewProjection_.UpdateMatrix();

	player_ = make_unique<Player>();
	player_->Initialize();

	mapCollisionManager_ = make_unique<MapCollisionManager>();
	MapManager::SetSelectMap(2);
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

		ImGui::TreePop();
	}

	if (SceneChange::GetScenChangeFlag())
	{
		Scene->ChangeState(new TitleScene);
		return;
	}


	player_->Update();
	
	MapManager::Update();
	mapCollisionManager_->ClearList();
	mapCollisionManager_->AddCollider(player_.get());
	mapCollisionManager_->ChackAllCollision();



	player_->Move();

	viewProjection_.UpdateMatrix();
	DebugTools::UpdateExecute(0);

	viewProjection_ = DebugTools::ConvertViewProjection(viewProjection_);
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	DebugTools::DrawExecute(0);

	player_->Draw(viewProjection_);
	MapManager::GetInstance()->Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}
