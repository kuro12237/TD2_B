#include "GoalHouse.h"

void GoalHouse::Initialize(Vector3 pos)
{
	testGoalModel_ = make_unique<Model>();
	testGoalModel_->CreateFromObj("TestBox");


	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	worldTransform_.UpdateMatrix();


	SetCollosionAttribute(kCollisionAttributeGoal);
	SetCollisionMask(kCollisionMaskGoal);
	SetObjectId(0b00001);
}

void GoalHouse::Update()
{
	worldTransform_.UpdateMatrix();
}

void GoalHouse::Draw(ViewProjection view)
{
	testGoalModel_->Draw(worldTransform_, view);
}


void GoalHouse::OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	LogManager::Log("hit\n");
	overlap, position, velocity,id;
}

void GoalHouse::OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap, position, velocity;
}

void GoalHouse::OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap, position, velocity;
}

void GoalHouse::OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap, position, velocity;
}

void GoalHouse::OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap, position, velocity;
}
