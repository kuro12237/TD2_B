#pragma once
#include"Model.h"
#include"VectorTransform.h"
#include"GameObject/MapCollisionManager/MapCollider.h"

class Buggage:public MapCollider
{
public:
	Buggage() {};
	~Buggage() {};

	void Initialize(Vector3 position);

	void Update();

	void Draw(ViewProjection view);

	void Move();

	void RightCollision()override { velocity_.x = 0; };
	void LeftCollision()override { velocity_.x = 0; };

	void TopCollision()override { velocity_.y = 0; };
	void DownCollision()override { velocity_.y = 0; };

	Vector3 GetWorldPosition()override { return worldTransform_.translate; }

private:

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_ = {};
	Vector3 velocity_ = {};
	float gravity = -0.1f;
};