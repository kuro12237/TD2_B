#include "Ground.h"

Ground* Ground::GetInstance()
{
	static Ground instance;
	return &instance;
}

void Ground::Initialize()
{
	if (!Ground::GetInstance()->InitializeLock)
	{
		Ground::GetInstance()->model_ = make_unique<Model>();
		Ground::GetInstance()->model_->CreateFromObj("MapGround");
		Ground::GetInstance()->worldTransform_.Initialize();
		Ground::GetInstance()->worldTransform_.scale = { 10,1,10 };
		Ground::GetInstance()->uvScale_.x = 24.0f;
		Ground::GetInstance()->worldTransform_.UpdateMatrix();
		Ground::GetInstance()->InitializeLock = true;
		Ground::GetInstance()->road_=make_unique<Road>();
		Ground::GetInstance()->road_->Initialize();
	}
}

void Ground::Update()
{
	Ground::GetInstance()->road_->Update();
	Ground::GetInstance()->worldTransform_.UpdateMatrix();
}

void Ground::Draw(ViewProjection view)
{
	Ground::GetInstance()->road_->Draw(view);
	Ground::GetInstance()->model_->Draw(Ground::GetInstance()->worldTransform_, view);
}
