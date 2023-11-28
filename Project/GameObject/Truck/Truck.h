#pragma once
#include"Model.h"
#define NumWheel 4;

class Truck
{
public:
	Truck() {};
	~Truck() {};

	void Initialize();

	void Update();
	
	void Draw(ViewProjection view);

	bool GetAlive() { return isAlive; }

private:

	unique_ptr<Model> bodyModel_ = nullptr;

	unique_ptr<Model>leftModel_[4] = {};
	unique_ptr<Model>RightModel_[4] = {};

	WorldTransform bodyWorldTransform_{};
	WorldTransform leftWorldTransform_[4] = {};
	WorldTransform RightWorldTransform_[4] = {};

	bool isAlive = true;

};