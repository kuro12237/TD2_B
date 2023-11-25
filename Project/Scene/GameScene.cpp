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
				PlayerPos.y = float(i + 1);
				PlayerPos.x = float(j);
				player_ = make_unique<Player>();
				player_->Initialize(PlayerPos);


			}

			if (map[i][j] == BAGGAGESPOWN)
			{
				BaggagePos.y = float(i + 1.5f);
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

	mapCollisionManager_ = make_unique<MapCollisionManager>();
	collisionManager_ = make_unique<CollisionManager>();

	viewProjection_.Initialize();
	viewProjection_.translation_.x = 7;
	viewProjection_.translation_.y = 7;
	viewProjection_.translation_.z = -39;
	viewProjection_.UpdateMatrix();

}

void GameScene::Update(GameManager* Scene)
{
	if (Input::PushKeyPressed(DIK_R))
	{
		Scene->ChangeState(new GameScene); return;
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

	viewProjection_.UpdateMatrix();
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
	player_->Draw(viewProjection_);
	MapManager::Draw(viewProjection_);

	TruckManager::Draw(viewProjection_);

	SkyBox::Draw(viewProjection_);
	Ground::Draw(viewProjection_);
	OffsideManager::Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}
