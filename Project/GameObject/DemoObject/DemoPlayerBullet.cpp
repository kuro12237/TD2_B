#include"DemoPlayerBullet.h"

void DemoPlayerBullet::Initialize(Vector3 position)
{
	model_ = make_unique<Model>();
	//ModelCubeStateはバグっているから基本使わないで
	model_->Initialize(new ModelCubeState);
	texHandle = TextureManager::LoadTexture("Resources/uvChecker.png");
	model_->SetTexHandle(texHandle);
	worldTransform_.Initialize();
	worldTransform_.translate = position;
	worldTransform_.UpdateMatrix();
	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionMaskPlayer);
}

void DemoPlayerBullet::Update()
{
	worldTransform_.translate.z += 0.1f;
	worldTransform_.UpdateMatrix();

}

void DemoPlayerBullet::Darw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}

Vector3 DemoPlayerBullet::GetWorldPosition()
{
	Vector3 result{};
	result.x = worldTransform_.matWorld.m[3][0];
	result.y = worldTransform_.matWorld.m[3][1];
	result.z = worldTransform_.matWorld.m[3][2];
	return result;
}

void DemoPlayerBullet::OnCollision()
{
	model_->SetColor({ 1,0,0,1 });
}
