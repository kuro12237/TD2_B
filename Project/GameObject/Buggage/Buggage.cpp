#include "Buggage.h"

void Buggage::Initialize(Vector3 position)
{
	model_ = make_unique<Model>();
	uint32_t tex = TextureManager::LoadTexture("Resources/uvChecker.png");
	model_->SetTexHandle(tex);
	model_->Initialize(new ModelSphereState);
	worldTransform_.Initialize();
	worldTransform_.translate = position;
	worldTransform_.UpdateMatrix();
}

void Buggage::Update()
{
	velocity_.y = velocity_.y + gravity;

	Vector2 v{};
	v.x = velocity_.x;
	v.y = velocity_.y;
	SetVelocity(v);
	SetRadious(0.5f);
	worldTransform_.UpdateMatrix();
}

void Buggage::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}

void Buggage::Move()
{
	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);
}
