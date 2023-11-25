#include "GoalHouse.h"

void GoalHouse::Initialize(Vector3 pos)
{
	testGoalModel_ = make_unique<Model>();
	testGoalModel_->CreateFromObj("TestBox");

	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	worldTransform_.UpdateMatrix();


}

void GoalHouse::Update()
{
	worldTransform_.UpdateMatrix();
}

void GoalHouse::Draw(ViewProjection view)
{
	testGoalModel_->Draw(worldTransform_, view);
}
