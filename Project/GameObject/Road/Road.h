#pragma once
#include"Model.h"


class Road
{
public:
	Road() {};
	~Road() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);


private:

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_ = {};

};
