#pragma once
#include"Model.h"
#include"VectorTransform.h"
#include"Input.h"
#include"GameObject/MapCollisionManager/MapCollider.h"

class Player:public MapCollider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();

	void Move();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override { return worldTransform_.translate; }


	void RightCollision()override;
	void LeftCollision()override;

	void TopCollision()override;
	void DownCollision()override;

private:

	void MapCollision();

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_{};

	float speed = 0.1f;
	Vector3 velocity_ = {};

};

