#include "Stage1.h"

void Stage1Scene::Initialize()
{
	MapManager::SetSelectMap(1);

	player_ = make_unique<Player>();
	player_->Initialize();

	mapCollisionManager_ = make_unique<MapCollisionManager>();
	collisionManager_ = make_unique<CollisionManager>();

	viewProjection_.Initialize();
	viewProjection_.translation_.x = 7;
	viewProjection_.translation_.y = 7;
	viewProjection_.translation_.z = -39;
	viewProjection_.UpdateMatrix();

	shared_ptr<Buggage> buggageA = make_shared<Buggage>();
	buggageA->SetPlayerWorldTransform(player_->GetWorldTransform());
	buggageA->Initialize({ 10,5,0 }, kCollisionAttributeEnemy, kCollisionMaskEnemy);

	buggages_.push_back(buggageA);
}

void Stage1Scene::Update(GameManager* Scene)
{
	if (Input::PushKeyPressed(DIK_R))
	{
		Scene->ChangeState(new Stage1Scene); return;
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

void Stage1Scene::Back2dSpriteDraw()
{
}

void Stage1Scene::Object3dDraw()
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

void Stage1Scene::Flont2dSpriteDraw()
{
}
