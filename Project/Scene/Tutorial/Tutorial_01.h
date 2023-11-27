#pragma once
#include"IScene.h"
#include"Model.h"
#include"ViewProjection.h"
#include"Input.h"
#include"GameManager.h"
#include"GameObject/GoalHouse/GoalHouse.h"


class Tutorial01Scene :public IScene
{
public:
	Tutorial01Scene() {};
	~Tutorial01Scene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	ViewProjection viewProjection_{};
};
