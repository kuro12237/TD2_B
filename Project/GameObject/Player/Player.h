#pragma once
#include"Model.h"
#include"VectorTransform.h"
#include"Input.h"
#include"GameObject/MapCollisionManager/MapCollider.h"
#include"BoxCollider.h"
#include"Collider/ColliderConfig.h"

class Player:public MapCollider,public BoxCollider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void GravityUpdate();

	void Update();

	void Move();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override { return worldTransform_.translate; }
	Vector3 GetVelocity() { return velocity_; }

	void RightCollision()override;
	void LeftCollision()override;

	void TopCollision()override;
	void DownCollision()override;

	void OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;
	
	void OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;
	void OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;

	void OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;
	void OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;


private:

	void Jamp();
		 
	void MapCollision();



	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_{};

	float speed = 0.1f;
	Vector3 velocity_ = {};
	float gravity = -0.1f;

	bool isJamp = false;
	uint32_t JampFrame = 0;
	Vector2 jampVelocity = {};

	bool isHit_ = false;
};

