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

};