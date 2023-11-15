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
		ImGui::Text("position %f %f %f", worldTransform_.translate.x, worldTransform_.translate.y, worldTransform_.translate.z);
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
	if (Input::PushKeyPressed(DIK_SPACE) && !isJamp)
	{
		JampFrame = 0;
		jampVelocity = { 0,0.1f };
		isJamp = true;	
		velocity_.y = 3;
	}

	//Jamp();

	velocity_.y = velocity_.y + gravity;
	Vector2 v = { velocity_.x,velocity_.y };


	SetVelocity(v);
	SetRadious(0.5f);
	worldTransform_.UpdateMatrix();

}

void Player::Move()
{
	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);
}

void Player::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}

void Player::RightCollision()
{
	velocity_.x = 0;
}

void Player::LeftCollision()
{
	velocity_.x = 0;
}

void Player::TopCollision()
{
	velocity_.y = 0;
}

void Player::DownCollision()
{
	velocity_.y = 0;
	isJamp = false;
}

void Player::Jamp()
{
	if (isJamp)
	{
		velocity_.y = 1;
	}
}

void Player::MapCollision()
{

}
