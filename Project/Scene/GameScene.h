#pragma once
#include"IScene.h"
#include"Pch.h"

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