#pragma once
#include"GameManager.h"
#include"IScene.h"

class Stage1Scene :public IScene
{
public:
	Stage1Scene() {};
	~Stage1Scene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	ViewProjection viewProjection_{};


};

