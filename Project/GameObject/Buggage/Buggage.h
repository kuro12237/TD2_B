#pragma once
#include"Model.h"
#include"VectorTransform.h"
#include"GameObject/MapCollisionManager/MapCollider.h"
#include"BoxCollider.h"
#include"Collider/ColliderConfig.h"
#include"Input.h"
#include"GameObject/MapManager/MapManager.h"
#include"GameObject/Offside/IOffside.h"
#include"GameObject/Offside/OffSideManager.h"

class Buggage:public MapCollider,public BoxCollider,public IOffside
{
public:
	Buggage() {};
	~Buggage() {};

	void Initialize(Vector3 position,uint32_t Attubte,uint32_t Mask);

	void Update();

	void Draw(ViewProjection view);

	void Move();

	void SetPlayerVelocity(Vector3 v);
	
	void RightCollision(uint32_t nowMapPos)override;
	void LeftCollision(uint32_t nowMapPos)override;

	void TopCollision(uint32_t nowMapPos)override;
	void DownCollision(uint32_t nowMapPos)override;

	Vector3 GetWorldPosition()override { return worldTransform_.translate; }
	void SetIsSelect(bool Selecr);
	
	void SetSelectDirection(uint32_t direction) { SelectDirection_ = direction; }

	void OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;

	void OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;
	void OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;

	void OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;
	void OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity)override;

	void SetPlayerPosition(Vector3 pos) { playerPos_ = pos; }
	void SetPlayerWorldTransform(WorldTransform worldTransform) { PlayerWorldTransform_ = worldTransform; }

	void SetOpenPortal(Vector3 pos);

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
	WorldTransform PlayerWorldTransform_ = {};

	float gravity = -0.1f;

	bool isHitWall=false;
	bool isHit_ = false;

	bool isSelect = false;

	uint32_t SelectDirection_ = Left;

	bool isOpenPortal_ = false;
};