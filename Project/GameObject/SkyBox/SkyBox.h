#pragma once
#include"Model.h"

class SkyBox
{
public:
	SkyBox() {};
	~SkyBox() {};

	static SkyBox* GetInstance();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);


private:

	bool InitializeLock = false;

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_ = {};

};
