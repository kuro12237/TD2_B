#include "DemoScene.h"

void DemoScene::Initialize()
{
	Grid* grid = new Grid();
	grid->Initialize();
	DebugTools::addCommand(grid,"grid");

	viewProjection_.Initialize({ 0,0,0.0f }, { 0.0f,3.0f,-20.0f });
	collisionManager_ = make_unique<CollisionManager>();

	demoPlayer_ = make_unique<DemoPlayer>();
	demoPlayer_->Initialize();

	demoEnemy_ = make_unique<DemoEnemy>();
	demoEnemy_->Initialize();
}


void DemoScene::Update(GameManager* Scene)
{
	Scene;
	demoPlayer_->Update();
	demoEnemy_->Update();
	
	CollisionFanc();

	DebugTools::UpdateExecute(0);

	viewProjection_.UpdateMatrix();
	viewProjection_ = DebugTools::ConvertViewProjection(viewProjection_);
}

void DemoScene::Back2dSpriteDraw()
{
	
}

void DemoScene::Object3dDraw()
{
	DebugTools::DrawExecute(0);
	demoPlayer_->Draw(viewProjection_);
	demoEnemy_->Draw(viewProjection_);
}

void DemoScene::Flont2dSpriteDraw()
{
}

void DemoScene::CollisionFanc()
{
	collisionManager_->ClliderClear();

	collisionManager_->ClliderPush(demoPlayer_.get());
	collisionManager_->ClliderPush(demoEnemy_.get());

	for (shared_ptr<DemoPlayerBullet>& bullet : demoPlayer_->GetPlayerBullets())
	{
		collisionManager_->ClliderPush(bullet.get());
	}

	collisionManager_->CheckAllCollision();

}
