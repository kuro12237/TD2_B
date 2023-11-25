#pragma once
#include"IScene.h"
#include"Model.h"
#include"ViewProjection.h"
#include"Input.h"
#include"GameManager.h"
#define STAGE_MAX 20

struct SelectScene_param
{
	bool IsSelect;

};

class SelectScene :public IScene
{
public:
	SelectScene() {};
	~SelectScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	void Contorol();

	void stage0_10(GameManager* Scene);

	ViewProjection viewProjection_ = {};

	array<unique_ptr<Sprite>,STAGE_MAX>model_ = {};
	array<WorldTransform,STAGE_MAX> worldTransform_ = {};
	array<SelectScene_param, STAGE_MAX> SelectParam_ = {};

	int SelectNumber = 0;
	bool SelectLock = false;

};