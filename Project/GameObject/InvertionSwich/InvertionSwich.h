#pragma once
#include"Model.h"
#include"GameObject/Offside/OffSideManager.h"
#include"BoxCollider.h"
#include"ColliderConfig.h"

class InvertionSwich:public BoxCollider
{
public:
	InvertionSwich() {};
	~InvertionSwich() {};

	void Initialize(Vector3 pos);

	void Update();

	void Draw(ViewProjection view);


	Vector3 GetWorldPosition()override { return worldTransform_.translate; }

	void OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;

	void OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;
	void OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;

	void OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;
	void OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;

	void Reset();

	void SetisHit(bool flag) { isHit_ = flag; }
	bool getIsHit() { return isHit_; }

private:

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_ = {};

	unique_ptr<Model>FoundationModel_ = nullptr;
	WorldTransform foundationWorldTransform_ = {};

	
	bool Lock_ = false;
	bool callbackCollisions = false;
	bool prevcallBackCollision = false;
	bool isHit_ = false;

};
