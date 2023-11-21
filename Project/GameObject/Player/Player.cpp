#include "Player.h"

void Player::Initialize()
{
	modelPlayerFace_ = make_unique<Model>();
	modelPlayerFace_->CreateFromObj("PlayerFace");
	modelPlayerBody_ = make_unique<Model>();
	modelPlayerBody_->CreateFromObj("PlayerBody");
	modelPlayerHat_ = make_unique<Model>();
	modelPlayerHat_->CreateFromObj("PlayerHat");
	modelPlayerLeftHand_ = make_unique<Model>();
	modelPlayerLeftHand_->CreateFromObj("PlayerLeft");
	modelPlayerRightHand_ = make_unique<Model>();
	modelPlayerRightHand_->CreateFromObj("PlayerRight");
	
	worldTransform_.Initialize();
	worldTransform_.translate = { 3,5,0 };
	worldTransform_.scale = { 0.2f,0.2f,0.2f };
	worldTransform_.rotation = { 0.0f,-2.0f,0.0f };
	//model_->SetColor({ 0,0,1,1 });

	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionMaskPlayer);
	
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
		worldTransform_.rotation.y = 2.0f;
	}
	else if (Input::PushKey(DIK_D))
	{
		velocity_.x = speed;
		worldTransform_.rotation.y = -2.0f;
	}

	if (Input::PushKey(DIK_W))
	{
		velocity_.y = speed;
	}
	if (Input::PushKey(DIK_S))
	{
		velocity_.y = -speed;
	}
	velocity_.y = velocity_.y + gravity;

	if (Input::PushKeyPressed(DIK_SPACE) && !isJamp)
	{
		JampFrame = 0;
		jampVelocity = { 0,0.0f };
		isJamp = true;	
	}

	Jamp();

	
	Vector2 v = { velocity_.x,velocity_.y };

	SetBoxVelocity(velocity_);
	SetVelocity(v);
	SetRadious(0.5f);


}

void Player::Move()
{

	isHit_ = false;
	
	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);
	worldTransform_.UpdateMatrix();

}

void Player::Draw(ViewProjection view)
{
	modelPlayerFace_->Draw(worldTransform_, view);
	modelPlayerBody_->Draw(worldTransform_, view);
	modelPlayerHat_->Draw(worldTransform_, view);
	modelPlayerLeftHand_->Draw(worldTransform_, view);
	modelPlayerRightHand_->Draw(worldTransform_, view);
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

void Player::OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	isHit_ = true;
	isJamp = false;
	position, velocity;
	
	velocity_.y += overlap.y;

	velocity_.x += overlap.x;
	
}

void Player::OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap;
	position;
	velocity;
}

void Player::OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap;
	position;
	velocity;
}

void Player::OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap;
	position;
	velocity;
}

void Player::OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap;
	position;
	velocity;
}

void Player::Jamp()
{
	if (JampFrame < 10)
	{
         velocity_.y += 0.5f;
		JampFrame++;
	}
}

void Player::MapCollision()
{

}
