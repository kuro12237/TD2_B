#pragma once
#include"Model.h"
#include"GameObject/MapManager/MapManager.h"
#include"BoxCollider.h"
#include"ColliderConfig.h"

class GoalHouse :public BoxCollider
{
public:
	GoalHouse() {};
	~GoalHouse() {};

	void Initialize(Vector3 pos);

	void Update();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override{return worldTransform_.translate;}


	void OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;

	void OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;
	void OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;

	void OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;
	void OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;



private:


	unique_ptr<Model>testGoalModel_ = nullptr;
	WorldTransform worldTransform_ = {};


};

