#pragma once
#include"Model.h"
#include"GameObject/MapManager/MapManager.h"

class GoalHouse
{
public:
	GoalHouse() {};
	~GoalHouse() {};

	void Initialize(Vector3 pos);

	void Update();

	void Draw(ViewProjection view);

private:


	unique_ptr<Model>testGoalModel_ = nullptr;
	WorldTransform worldTransform_ = {};


};

