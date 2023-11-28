#include "GoalHouse.h"

void GoalHouse::Initialize(Vector3 pos)
{
	testGoalModel_ = make_unique<Model>();
	testGoalModel_->CreateFromObj("TestBox");


	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	worldTransform_.UpdateMatrix();

	Vector3 spownHousePos = pos;
	spownHousePos.y -= 0.5f;
	spownHousePos.z += 1.0f;

	house_ = make_unique<House>();
	house_->Initialize(spownHousePos,{0.25f,0.25f,0.25f});
	SetCollosionAttribute(kCollisionAttributeGoal);
	SetCollisionMask(kCollisionMaskGoal);
	SetObjectId(0b00001);
}

void GoalHouse::Update()
{
	house_->Update();
	worldTransform_.UpdateMatrix();
}

void GoalHouse::Draw(ViewProjection view)
{
	house_->Draw(view);
	//testGoalModel_->Draw(worldTransform_, view);
}


void GoalHouse::OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	LogManager::Log("hit\n");
	overlap, position, velocity,id;
}

void GoalHouse::OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	overlap, position, velocity,id;
}

void GoalHouse::OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	overlap, position, velocity,id;
}

void GoalHouse::OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	overlap, position, velocity,id;
}

void GoalHouse::OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	overlap, position, velocity,id;
}
