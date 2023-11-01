#include"DemoEnemy.h"

void DemoEnemy::Initialize()
{
	model_ = make_unique<Model>();
	model_->Initialize(new ModelSphereState);
	model_->SetColor({ 0,1,0,1 });
	texHandle = TextureManager::LoadTexture("Resources/uvChecker.png");
	model_->SetTexHandle(texHandle);
	worldTransform_.Initialize();
	worldTransform_.translate.z = 10;
	worldTransform_.translate.y = 1;
	worldTransform_.UpdateMatrix();
	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionMaskEnemy);
}

void DemoEnemy::Update()
{
	worldTransform_.UpdateMatrix();
}

void DemoEnemy::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}

Vector3 DemoEnemy::GetWorldPosition()
{
	Vector3 result{};
	result.x = worldTransform_.matWorld.m[3][0];
	result.y = worldTransform_.matWorld.m[3][1];
	result.z = worldTransform_.matWorld.m[3][2];
	return result;
}

void DemoEnemy::OnCollision()
{

}
