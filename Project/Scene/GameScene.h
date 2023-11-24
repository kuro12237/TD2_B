#pragma once
#include"IScene.h"
#include"Pch.h"
#include"LogManager.h"
#include"GameObject/SceneChange/SceneChange.h"
#include"Scene/Title/TitleScene.h"
#include"GameObject/MapManager/MapManager.h"
#include"GameObject/MapCollisionManager/MapCollisionManager.h"
#include"GameObject/Player/Player.h"
#include"GameObject/Buggage/Buggage.h"
#include"CollisionManager.h"

#include"GameObject/SkyBox/SkyBox.h"
#include"GameObject/Ground/Ground.h"
#include"GameObject/Truck/TruckManager.h"
#include"GameObject/Offside/OffSideManager.h"

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
	
	unique_ptr<Player>player_ = nullptr;
	list<shared_ptr<Buggage>>buggages_ ;


	ViewProjection viewProjection_{};
	

	unique_ptr<CollisionManager> collisionManager_ = nullptr;
	unique_ptr<MapCollisionManager> mapCollisionManager_ = nullptr;
};