#include "GameScene.h"

void GameScene::Initialize()
{
	MapManager::Update();

	array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map = {};

	//マップチップ反転Y
	for (int i = 0; i < MapTip_MAX_Y; i++)
	{
		for (int j = 0; j < MapTip_MAX_X; j++)
		{
			map[MapTip_MAX_Y - i - 1][j] = MapManager::GetNowMapTip()[i][j];
		}
	}

	Vector3 PlayerPos = { 0,0,0 };
	Vector3 BaggagePos = {};
	uint32_t BaggageCount = 0;
	for (int i = 0; i < MapTip_MAX_Y; i++)
	{
		for (int j = 0; j < MapTip_MAX_X; j++)
		{
			if (map[i][j] == START)
			{
				PlayerPos.y = float(i + 1.5f);
				PlayerPos.x = float(j);
				player_ = make_unique<Player>();
				player_->Initialize(PlayerPos);


			}
		}
	}

	for (int i = 0; i < MapTip_MAX_Y; i++)
	{
		for (int j = 0; j < MapTip_MAX_X; j++)
		{

			if (map[i][j] == BAGGAGESPOWN)
			{
				BaggagePos.y = float(i + 1.7f);
				BaggagePos.x = float(j);

				shared_ptr<Buggage> buggageA = make_shared<Buggage>();
				buggageA->SetPlayerWorldTransform(player_->GetWorldTransform());
				if (BaggageCount == 0)
				{
					buggageA->Initialize(BaggagePos, kCollisionAttributeEnemy, kCollisionMaskEnemy);
				}
				if (BaggageCount == 1)
				{
					buggageA->Initialize(BaggagePos, kCollisionAttributeEnemy2, kCollisionMaskEnemy2);
				}

				buggages_.push_back(buggageA);
				BaggageCount++;
			}
		}
	}

	for (int i = 0; i < MapTip_MAX_Y; i++)
	{
		for (int j = 0; j < MapTip_MAX_X; j++)
		{
			if (map[i][j] == GOAL)
			{
				Vector3 goalPos = {};
				goal_ = make_unique<GoalHouse>();

				goalPos.x = float(j);
				goalPos.y = float(i + 1.5f);

				goal_->Initialize(goalPos);

			}
		}
	}

	for (int i = 0; i < MapTip_MAX_Y; i++)
	{
		for (int j = 0; j < MapTip_MAX_X; j++)
		{
			if (map[i][j] == INVERSIONSWICH)
			{
				Vector3 pos{};
				pos.x = float(j);
				pos.y = float(i + 1.5f);

				shared_ptr<InvertionSwich>invertion_ = make_shared<InvertionSwich>();
				invertion_->Initialize(pos);
				invertionSwichs_.push_back(invertion_);
			}
		}
	}

	mapCollisionManager_ = make_unique<MapCollisionManager>();
	collisionManager_ = make_unique<CollisionManager>();
	OffsideManager::SetDirection(Right);

	playerCamera_ = make_unique<PlayerCamera>();
	playerCamera_->Initialize();

	uint32_t tex = TextureManager::LoadTexture("Resources/ContorolExplain.png");
	contorolSprite_ = make_unique<Sprite>();
	contorolSprite_->SetTexHandle(tex);
	contorolSprite_->Initialize(new SpriteBoxState, { 0,0 }, { 1280,720 });
	contorolWorldTransform_.Initialize();
	contorolWorldTransform_.translate.x = 640;
	contorolWorldTransform_.translate.y = 360;
	viewProjection_.Initialize();
	viewProjection_.translation_.x = 7;
	viewProjection_.translation_.y = 7;
	viewProjection_.translation_.z = -39;
	viewProjection_.UpdateMatrix();

}

void GameScene::Update(GameManager* Scene)
{
	player_->GravityUpdate();

	Collision();

	player_->Update();
	playerCamera_->Update(player_->GetWorldPosition());
	OffsideManager::Update();
	goal_->Update();

	if (buggages_.remove_if([](shared_ptr<Buggage>& b) {
		if (!b->GetAlive())
		{
			b.reset();
			return true;
		}
		return false;
		}))
	{
		if (buggages_.size() == 0)
		{
			SceneChange::ChangeStart();
		}
	}

	
	for (shared_ptr<Buggage>& buggage : buggages_)
	{

	
		buggage->SetIsSelect(player_->GetIsBuggageSelect());
		


		buggage->SetSelectDirection(player_->GetIsBuggageSelectDirection());
		buggage->SetPlayerPosition(player_->GetWorldPosition());
		buggage->SetPlayerWorldTransform(player_->GetWorldTransform());
		buggage->Update();
	}




	OffsideManager::ClearList();
	for (shared_ptr<Buggage>& buggage : buggages_)
	{
		OffsideManager::AddList(buggage.get());
	}
	OffsideManager::CheckAllOffside();

	for (shared_ptr<InvertionSwich>& invertion : invertionSwichs_)
	{
		invertion->Update();
		invertion->Reset();
	}

	//Mapの当たり判定
	MapManager::Update();
	MapCollision();

	

	for (shared_ptr<Buggage>& buggage : buggages_)
	{
		buggage->Move();
	}

	player_->Move();

	SkyBox::Update();
	Ground::Update();
	TruckManager::Update();

	contorolWorldTransform_.UpdateMatrix();
	viewProjection_.UpdateMatrix();
	viewProjection_ = playerCamera_->GetViewProjection();

	if (buggages_.size() == 0)
	{
		if (SceneChange::GetScenChangeFlag())
		{
			if (MapManager::GetNowStageNumber()+1>20)
			{
				Scene->ChangeState(new TitleScene);
				return;
			}
			MapManager::SetSelectMap(MapManager::GetNowStageNumber()+1);
			Scene->ChangeState(new GameScene);
			return;
		}
	}
	if (isReset_)
	{
		if (SceneChange::GetScenChangeFlag())
		{
			Scene->ChangeState(new GameScene);
			return;
		}
	}
	if (isSelectScene_)
	{
		if (SceneChange::GetScenChangeFlag())
		{
			Scene->ChangeState(new SelectScene);
			return;
		}
	}

	if (Input::PushKeyPressed(DIK_T))
	{
		isSelectScene_ = true;
		SceneChange::ChangeStart();
	}

	if (Input::PushKeyPressed(DIK_R))
	{
		isReset_ = true;
		SceneChange::ChangeStart();
	}
	XINPUT_STATE joyState{};
	Input::NoneJoyState(joyState);
	if (Input::GetInstance()->GetJoystickState(joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			isReset_ = true;
			SceneChange::ChangeStart();
		}
	}
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	for (shared_ptr<Buggage>& buggage : buggages_)
	{
		buggage->Draw(viewProjection_);
	}
	
	for (shared_ptr<InvertionSwich>& invertion : invertionSwichs_)
	{
		invertion->Draw(viewProjection_);
	}

	player_->Draw(viewProjection_);

	goal_->Draw(viewProjection_);

	MapManager::Draw(viewProjection_);

	TruckManager::Draw(viewProjection_);

	SkyBox::Draw(viewProjection_);
	Ground::Draw(viewProjection_);
	OffsideManager::Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
	contorolSprite_->Draw(contorolWorldTransform_);
}

void GameScene::Collision()
{
	//objectの当たり判定
	collisionManager_->ClliderClear();
	collisionManager_->BoxColliderPush(player_.get());
	collisionManager_->BoxColliderPush(goal_.get());
	
	for (shared_ptr<InvertionSwich>& invertion : invertionSwichs_)
	{
		collisionManager_->BoxColliderPush(invertion.get());
	}

	for (shared_ptr<Buggage>& buggage : buggages_)
	{
		collisionManager_->BoxColliderPush(buggage.get());
	}
	collisionManager_->CheckAllCollision();

}

void GameScene::MapCollision()
{
	mapCollisionManager_->ClearList();
	mapCollisionManager_->AddCollider(player_.get());
	for (shared_ptr<Buggage>& buggage : buggages_)
	{
		mapCollisionManager_->AddCollider(buggage.get());
	}
	mapCollisionManager_->ChackAllCollision();

}
