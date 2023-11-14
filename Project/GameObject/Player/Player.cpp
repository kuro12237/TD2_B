#include "Player.h"

void Player::Initialize()
{
	model_ = make_unique<Model>();
	model_->CreateFromObj("TestBox");
	worldTransform_.Initialize();
	worldTransform_.translate = { 3,5,0 };
	model_->SetColor({ 0,0,1,1 });
}

void Player::Update()
{

	if (ImGui::TreeNode("Player"))
	{
	
		ImGui::SliderFloat("speed", &speed,-1.0f,1.0f);
		ImGui::TreePop();
	}
	velocity_ = {};

	if (Input::PushKey(DIK_A))
	{
		velocity_.x = -speed;
	}
	if (Input::PushKey(DIK_D))
	{
		velocity_.x = speed;
	}

	if (Input::PushKey(DIK_W))
	{
		velocity_.y = speed;
	}
	if (Input::PushKey(DIK_S))
	{
		velocity_.y = -speed;
	}

	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);

	worldTransform_.UpdateMatrix();

}

void Player::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}
