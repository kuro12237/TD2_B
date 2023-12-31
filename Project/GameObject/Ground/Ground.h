#pragma once
#include"Model.h"
#include"GameObject/Road/Road.h"


class Ground
{
public:
	Ground() {};
	~Ground() {};

	static Ground* GetInstance();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);

private:

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_ = {};
	bool InitializeLock = false;
	Vector3 uvScale_ = { 1,1,1 };

	unique_ptr<Road>road_ = nullptr;

};
