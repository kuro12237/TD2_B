#include "GameScene.h"

void GameScene::Initialize()
{
	DebugCamera* debugCamera = new DebugCamera();
	debugCamera->Initialize();
	DebugTools::addCommand(debugCamera,"d");

	LogManager::Log("GameScene_1\n");
	//MapManager::Initialize();
	viewProjection_.Initialize();
	viewProjection_.translation_.x = 7;
	viewProjection_.translation_.y = 7;
	viewProjection_.translation_.z = -39;
	viewProjection_.UpdateMatrix();

	player_ = make_unique<Player>();
	player_->Initialize();

	mapCollisionManager_ = make_unique<MapCollisionManager>();
	MapManager::SetSelectMap(2);

	collisionManager_ = make_unique<CollisionManager>();

	OffsideManager::Initialize();
	
	shared_ptr<Buggage> buggageA = make_shared<Buggage>();
	buggageA->SetPlayerWorldTransform(player_->GetWorldTransform());
	buggageA->Initialize({ 10,5,0 },kCollisionAttributeEnemy,kCollisionMaskEnemy);

	buggages_.push_back(buggageA);

	//shared_ptr<Buggage> buggageB = make_shared<Buggage>();
	//buggageB->SetPlayerWorldTransform(player_->GetWorldTransform());
	//buggageB->Initialize({ 7,7,0 },kCollisionAttributeEnemy2,kCollisionMaskEnemy2);

	//buggages_.push_back(buggageB);
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

	player_->GravityUpdate();

	//objectの当たり判定
	collisionManager_->ClliderClear();
	collisionManager_->BoxColliderPush(player_.get());
	for (shared_ptr<Buggage>& buggage : buggages_)
	{
		collisionManager_->BoxColliderPush(buggage.get());
	}
	collisionManager_->CheckAllCollision();


	player_->Update();
	OffsideManager::Update();

	for (shared_ptr<Buggage>& buggage : buggages_)
	{
		buggage->SetIsSelect(player_->GetIsBuggageSelect());
		buggage->SetSelectDirection(player_->GetIsBuggageSelectDirection());
		buggage->SetPlayerPosition(player_->GetWorldPosition());
		buggage->SetPlayerWorldTransform(player_->GetWorldTransform());
		buggage->Update();
	}

	//Mapの当たり判定
	MapManager::Update();
	mapCollisionManager_->ClearList();
	mapCollisionManager_->AddCollider(player_.get());

	for (shared_ptr<Buggage>& buggage : buggages_)
	{
		mapCollisionManager_->AddCollider(buggage.get());
	}
	mapCollisionManager_->ChackAllCollision();

	OffsideManager::ClearList();
	
	for (shared_ptr<Buggage>& buggage : buggages_)
	{
		OffsideManager::AddList(buggage.get());
	}
	OffsideManager::CheckAllOffside();


	for (shared_ptr<Buggage>& buggage : buggages_)
	{
		buggage->Move();
	}

	player_->Move();

	SkyBox::Update();
	Ground::Update();
	TruckManager::Update();
	//OffsideManager::SetPlayerPos(player_->GetWorldPosition());
	
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


	for (shared_ptr<Buggage>& buggage : buggages_)
	{
		buggage->Draw(viewProjection_);
	}
	player_->Draw(viewProjection_);
	MapManager::GetInstance()->Draw(viewProjection_);

	TruckManager::Draw(viewProjection_);
	
	SkyBox::Draw(viewProjection_);
	Ground::Draw(viewProjection_);
	OffsideManager::Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}
