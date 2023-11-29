#pragma once
#include"Model.h"
#include"VectorTransform.h"
#include"Input.h"
#include"GameObject/MapCollisionManager/MapCollider.h"
#include"BoxCollider.h"
#include"Collider/ColliderConfig.h"
#include"GameObject/MapManager/MapManager.h"
#include"GameObject/Offside/OffSideManager.h"
#include"Audio/AudioManager.h"
#define SELECT_MODEL_MAX 2


class Player:public MapCollider,public BoxCollider
{
public:
	Player() {};
	~Player() {};

	void Initialize(Vector3 pos);

	void GravityUpdate();

	void Update();

	void Move();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override { return worldTransform_.translate; }
	Vector3 GetVelocity() { return velocity_; }
	WorldTransform GetWorldTransform() { return worldTransform_; }

	bool GetIsBuggageSelect() { return isBuggagesSelect; }
	uint32_t GetIsBuggageSelectDirection() { return BuggageSelectDirection; }

	void SetisSetBuggate(bool flag) { isBuggagesSelect = flag; }

	void RightCollision(uint32_t nowMapPos)override;
	void LeftCollision(uint32_t nowMapPos)override;

	void TopCollision(uint32_t nowMapPos)override;
	void DownCollision(uint32_t nowMapPos)override;

	void OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;
	
	void OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;
	void OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;

	void OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;
	void OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)override;


private:

	void KeyControl();

	void GamePadContorol();

	void Jamp();
		 
	void SelectBox();

	unique_ptr<Model>modelPlayerFace_ = nullptr;
	unique_ptr<Model>modelPlayerBody_ = nullptr;
	unique_ptr<Model>modelPlayerHat_ = nullptr;
	unique_ptr<Model>modelPlayerLeftHand_ = nullptr;
	unique_ptr<Model>modelPlayerRightHand_ = nullptr;
	WorldTransform worldTransform_{};

	float speed = 0.1f;
	Vector3 velocity_ = {};
	float gravity = -0.1f;

	bool isJamp = false;
	uint32_t JampFrame = 0;
	Vector2 jampVelocity = {};

	bool isHit_ = false;

	uint32_t nowMapPos_ = {};

	bool isBuggagesSelect = false;
	uint32_t BuggageSelectDirection = Left;

	unique_ptr<Model>SelectModel_ = {};
	WorldTransform SelectWorldTransform = {};

	uint32_t Audiohandle_ = 0;

	uint32_t NotSetBaggage_ = 0;
	uint32_t SetBaggage_ = 0;
};

