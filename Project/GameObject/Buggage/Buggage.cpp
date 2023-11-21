#include "Buggage.h"

void Buggage::Initialize(Vector3 position, uint32_t Attubte, uint32_t Mask)
{
	model_ = make_unique<Model>();
	uint32_t tex = TextureManager::LoadTexture("Resources/uvChecker.png");
	model_->SetTexHandle(tex);
	model_->Initialize(new ModelSphereState);
	worldTransform_.Initialize();
	worldTransform_.translate = position;
	worldTransform_.UpdateMatrix();

	SetCollosionAttribute(Attubte);
	SetCollisionMask(Mask);
}

void Buggage::Update()
{
	if (ImGui::TreeNode("Baggage"))
	{
		ImGui::Text("position %f %f %f", worldTransform_.translate.x, worldTransform_.translate.y, worldTransform_.translate.z);
		ImGui::Text("Velocity %f %f %f", velocity_.x, velocity_.y, velocity_.z);
		ImGui::TreePop();
	}

	
	if (!isHit_)
	{
		velocity_.x = 0;
	}
	
	velocity_.y = velocity_.y + gravity;

	Vector2 v{};
	v.x = velocity_.x;
	v.y = velocity_.y;

	SetVelocity(v);
	SetBoxVelocity(velocity_);
	SetRadious(0.5f);

}

void Buggage::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}

void Buggage::Move()
{
	isHit_ = false;
	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);
	worldTransform_.UpdateMatrix();
}

void Buggage::SetPlayerVelocity(Vector3 v)
{
	if (isHit_)
	{
		playerVelocity_ = v;
	}
}

void Buggage::SetPlayerPosition(Vector3 v)
{
	playerPos_ = v;
}

void Buggage::RightCollision()
{
	velocity_.x = 0;
	playerVelocity_.x = 0;
	isHitWall = true;
};

void Buggage::LeftCollision()
{
   velocity_.x = 0; 
   playerVelocity_.x = 0;
   isHitWall = true;
}

void Buggage::TopCollision()
{
	velocity_.y = 0;
	playerVelocity_.y = 0;
	//isHitWall = false;
};
void Buggage::DownCollision()
{
	velocity_.y = 0;
	playerVelocity_.y = 0;
	//isHitWall = false;

};

void Buggage::OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	isHit_ = true;

	if (position.y + 0.3f >= worldTransform_.translate.y &&
		position.y - 0.3f <= worldTransform_.translate.y)
	{

		velocity_.x = velocity.x;

		velocity_.x -= overlap.x;


	}

}

void Buggage::OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap;
	position;
	velocity;

}

void Buggage::OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap;
	position;
	velocity;
}

void Buggage::OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap;
	position;
	velocity;
}

void Buggage::OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap;
	position;
	velocity;
}
