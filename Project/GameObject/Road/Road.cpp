#include "Road.h"

void Road::Initialize()
{
	model_ = make_unique<Model>();
	model_->CreateFromObj("Road");
	model_->SetUvScale({ 60,1,6 });
	//50
	worldTransform_.Initialize();
	worldTransform_.translate.z += 24;
	worldTransform_.translate.y = 0.01f;
	worldTransform_.scale = { 60,1,6 };
	worldTransform_.UpdateMatrix();
}

void Road::Update()
{	
	worldTransform_.UpdateMatrix();
}

void Road::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}
