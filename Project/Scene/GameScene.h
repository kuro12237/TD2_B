#pragma once
#include"IScene.h"
#include"Pch.h"
#include"LogManager.h"
#include"GameObject/SceneChange/SceneChange.h"
#include"Scene/Title/TitleScene.h"
#include"GameObject/MapManager/MapManager.h"
#include"GameObject/MapCollisionManager/MapCollisionManager.h"
#include"GameObject/Player/Player.h"
#include"GameObject/PlayerCamera/PlayerCamera.h"
#include"GameObject/Buggage/Buggage.h"
#include"CollisionManager.h"

#include"GameObject/SkyBox/SkyBox.h"
#include"GameObject/Ground/Ground.h"
#include"GameObject/Truck/TruckManager.h"
#include"GameObject/Offside/OffSideManager.h"
#include"GameObject/GoalHouse/GoalHouse.h"
#include"GameManager.h"
#include"GameObject/InvertionSwich/InvertionSwich.h"
#include"GameObject/StageTitleName/StageTitleName.h"

class GameScene :public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;
private:
	
	void Collision();
	
	void MapCollision();

	unique_ptr<Player>player_ = nullptr;
	unique_ptr<PlayerCamera>playerCamera_ = nullptr;
	unique_ptr<GoalHouse>goal_ = nullptr;
	
	list<shared_ptr<Buggage>>buggages_ ;
	list<shared_ptr<InvertionSwich>>invertionSwichs_;

	ViewProjection viewProjection_{};
	

	unique_ptr<CollisionManager> collisionManager_ = nullptr;
	unique_ptr<MapCollisionManager> mapCollisionManager_ = nullptr;


	bool isReset_ = false;
	bool isSelectScene_ = false;

	unique_ptr<Sprite>contorolSprite_ = nullptr;
	WorldTransform contorolWorldTransform_{};


	uint32_t Audiohandle_ = 0;
	

	unique_ptr<Sprite>stageButtonASprite_ = nullptr;
	WorldTransform stageButtonAWorldTransform_{};

	unique_ptr<Sprite>stageButtonBSprite_ = nullptr;
	WorldTransform stageButtonBWorldTransform_{};

	unique_ptr<Sprite>stageButtonYSprite_ = nullptr;
	WorldTransform stageButtonYWorldTransform_{};

	unique_ptr<Sprite>stageButtonHomeSprite_ = nullptr;
	WorldTransform stageButtonHomeWorldTransform_{};

	bool isPlayingAudio_ = false;
	int time_ = 0;

	bool isPlayingAudio2_ = false;
	int time2_ = 0;
};