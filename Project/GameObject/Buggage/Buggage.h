#pragma once
#include"Model.h"
#include"VectorTransform.h"
#include"GameObject/MapCollisionManager/MapCollider.h"
#include"BoxCollider.h"
#include"Collider/ColliderConfig.h"
#include"Input.h"
#include"GameObject/MapManager/MapManager.h"
class Buggage:public MapCollider,public BoxCollider
{
public:
	Buggage() {};
	~Buggage() {};

	void Initialize(Vector3 position,uint32_t Attubte,uint32_t Mask);

	void Update();

	void Draw(ViewProjection view);

	void Move();

	void SetPlayerVelocity(Vector3 v);
	
	void RightCollision()override;
	void LeftCollision()override;

	void TopCollision()override;
	void DownCollision()override;

	Vector3 GetWorldPosition()override { return worldTransform_.translate; }
	void OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;

	void OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;
	void OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;

	void OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;
	void OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;

	void SetPlayerPosition(Vector3 pos) { playerPos_ = pos; }

private:

	/// <summary>
	/// 選択関数
	/// </summary>
	void SelectBox();

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_ = {};
	Vector3 velocity_ = {};
	
	Vector3 playerVelocity_ = {};
	Vector3 playerPos_ = {};

	float gravity = -0.1f;

	bool isHitWall=false;
	bool isHit_ = false;

	bool isSelect = false;
};