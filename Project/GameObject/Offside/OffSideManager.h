#pragma once
#include"Model.h"
#include"IOffside.h"
#include"GameObject/MapManager/Data/MapData.h"
#include"BoxCollider.h"

class OffsideManager
{
public:
	OffsideManager() {};
	~OffsideManager() {};

	static OffsideManager* GetInstance();

	static void ClearList() { OffsideManager::GetInstance()->offsides_.clear(); }

	static void SetPlayerPos(Vector3 pos) { OffsideManager::GetInstance()->offsidePos_ = pos; }

	static void AddList(IOffside *offside) { OffsideManager::GetInstance()->offsides_.push_back(offside); }

	static void CheckAllOffside();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);

	static Vector3 GetOffsidePos() { return OffsideManager::GetInstance()->offsidePos_; }
	static bool GetOffsideDirection() { return OffsideManager::GetInstance()->Direction_; }

	static void SetDirection(uint32_t d) { OffsideManager::GetInstance()->Direction_ = d; }
	static uint32_t GetDirection() { return OffsideManager::GetInstance()->Direction_; }

private:

	bool ChackRightOffside();

	Vector3 offsidePos_ = {};

	list<IOffside*>offsides_;
	uint32_t Direction_ = Right;

	unique_ptr<Model>leftModel_ = nullptr;
	WorldTransform leftWorldTransform_{};

	unique_ptr<Model>rightModel_ = nullptr;
	WorldTransform rightWorldTransform_{};

	bool InitialiseLock_ = false;

	Vector4 color_ = { 1,1,1,1 };
	bool testDirectionFlag_ = false;
};

