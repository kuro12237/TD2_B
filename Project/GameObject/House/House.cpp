#include "House.h"

void House::Initialize(Vector3 position, Vector3 scale)
{
	worldTransform_.Initialize();
	worldTransform_.translate = position;
	worldTransform_.scale = scale;
	worldTransform_.UpdateMatrix();

	model_ = make_unique<Model>();
	model_->CreateFromObj("House");
	
}

void House::Update()
{

	worldTransform_.UpdateMatrix();
}

void House::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}
