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
		Ground::GetInstance()->worldTransform_.scale.x = 10;
		Ground::GetInstance()->uvScale_.x = 24.0f;
		Ground::GetInstance()->worldTransform_.UpdateMatrix();
		Ground::GetInstance()->InitializeLock = true;
	}
}

void Ground::Update()
{
	ImGui::Begin("Ground");

	ImGui::DragFloat3("s", &Ground::GetInstance()->uvScale_.x,-1.0f,1.0f);
	Ground::GetInstance()->model_->SetUvScale(Ground::GetInstance()->uvScale_);
	ImGui::End();

	Ground::GetInstance()->worldTransform_.UpdateMatrix();
}

void Ground::Draw(ViewProjection view)
{
	Ground::GetInstance()->model_->Draw(Ground::GetInstance()->worldTransform_, view);
}
