#pragma once
#include"Model.h"
#include"VectorTransform.h"
#include"GameObject/MapCollisionManager/MapCollider.h"
#include"BoxCollider.h"
#include"Collider/ColliderConfig.h"

class Buggage:public MapCollider,public BoxCollider
{
public:
	Buggage() {};
	~Buggage() {};

	void Initialize(Vector3 position);

	void Update();

	void Draw(ViewProjection view);

	void Move();

	void SetPlayerVelocity(Vector3 v) { playerVelocity_ = v; }

	void RightCollision()override;
	void LeftCollision()override;

	void TopCollision()override;
	void DownCollision()override;

	Vector3 GetWorldPosition()override { return worldTransform_.translate; }
	void OnCollision()override;


private:

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_ = {};
	Vector3 velocity_ = {};
	Vector3 playerVelocity_ = {};
	float gravity = -0.1f;

	bool isHitWall = false;
};