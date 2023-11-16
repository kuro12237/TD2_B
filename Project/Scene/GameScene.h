#pragma once

#include"IScene.h"
#include"Pch.h"
#include"LogManager.h"
#include"GameObject/SceneChange/SceneChange.h"
#include"Scene/Title/TitleScene.h"
#include"SlectStage/SlectStage.h"
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
	
	
	
};