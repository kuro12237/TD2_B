#pragma once
#include"Model.h"


class House
{
public:
	House() {};
	~House() {};

	void Initialize(Vector3 position,Vector3 scale);

	void Update();

	void Draw(ViewProjection view);


private:

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_ = {};

	unique_ptr<Model>woodModel_ = nullptr;
	WorldTransform woodWorldTransform{};
};
