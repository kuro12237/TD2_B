#pragma once
#include"Model.h"
#include"VectorTransform.h"
#include"Input.h"

class Player
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition() { return worldTransform_.translate; }

private:

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_{};


	float speed = 0.1f;
	Vector3 velocity_ = {};

};

