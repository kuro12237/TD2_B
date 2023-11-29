#pragma once
#include"Model.h"
#include"Sprite/Sprite.h"
#include"GameObject/MapManager/MapManager.h"
#define STAGE_TITLE_NAME 10

class StageTitleName
{
public:

	static StageTitleName* GetInstance();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);

private:

	static void LoadTexs();

	unique_ptr<Sprite>sprites_ = {};
	WorldTransform worldTransform = {};
	uint32_t tex[STAGE_TITLE_NAME] = {};
	bool isPrintFlag_[STAGE_TITLE_NAME] = {};


};