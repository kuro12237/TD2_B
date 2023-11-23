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
		Ground::GetInstance()->InitializeLock = true;
	}
}

void Ground::Update()
{
	Ground::GetInstance()->worldTransform_.UpdateMatrix();
}

void Ground::Draw(ViewProjection view)
{
	Ground::GetInstance()->model_->Draw(Ground::GetInstance()->worldTransform_, view);
}
