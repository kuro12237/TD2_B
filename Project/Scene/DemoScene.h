#pragma once
#include"IScene.h"
#include"GameObject/DemoObject/DemoPlayer.h"
#include"GameObject/DemoObject/DemoEnemy.h"
#include"CollisionManager.h"
#include"DebugTools/DebugTools.h"

class DemoScene :public IScene
{
public:
	DemoScene() {};
	~DemoScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	void CollisionFanc();
	
	unique_ptr<CollisionManager>collisionManager_ = nullptr;

	ViewProjection viewProjection_{};
	unique_ptr<DemoPlayer>demoPlayer_ = nullptr;
	unique_ptr<DemoEnemy>demoEnemy_ = nullptr;

};


