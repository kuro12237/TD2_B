#pragma once
#include"Scene/GameScene.h"
#define SCENECHANGE_SPRITE_MAX 40

class SlectScene
{
public:
	static SlectScene* GetInstance();
	static void Initilize();
	static void Updata();
	static void Draw();

private:


	uint32_t texHandle = 1;

	unique_ptr<Sprite>sprite_[SCENECHANGE_SPRITE_MAX] = {};

	WorldTransform worldTransform_[SCENECHANGE_SPRITE_MAX]{};


	bool DrawFlag = false;

	bool isStart_ = false;

	bool isEnd_ = false;

	uint32_t EndTimer_ = 0;
	const uint32_t EndTimerMax_ = 60;

	bool SceneChangeFlag = false;

	bool isUpdate = false;


};

