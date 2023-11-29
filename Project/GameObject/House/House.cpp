#include "House.h"

void House::Initialize(Vector3 position, Vector3 scale)
{
	worldTransform_.Initialize();
	worldTransform_.translate = position;
	worldTransform_.scale = scale;
	worldTransform_.UpdateMatrix();

	model_ = make_unique<Model>();
	model_->CreateFromObj("House");
	
	woodWorldTransform.Initialize();
	woodWorldTransform.translate = position;
	woodWorldTransform.translate.y -= 0.5f;
	woodWorldTransform.scale = {1.8f,1.0f,1.0f};
	woodWorldTransform.UpdateMatrix();

	woodModel_ = make_unique<Model>();
	woodModel_->CreateFromObj("TestBox");
	uint32_t WoodTex = TextureManager::LoadTexture("Resources/BlockTex/woodTex.png");
	woodModel_->SetTexHandle(WoodTex);
}

void House::Update()
{
	woodWorldTransform.UpdateMatrix();
	worldTransform_.UpdateMatrix();
}

void House::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
	woodModel_->Draw(woodWorldTransform, view);
}
