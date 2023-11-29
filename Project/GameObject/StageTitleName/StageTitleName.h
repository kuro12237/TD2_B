#pragma once
#include"Model.h"
#include"Sprite/Sprite.h"
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
	
	unique_ptr<Sprite>sprites_[STAGE_TITLE_NAME] = {};
	WorldTransform worldTransform[STAGE_TITLE_NAME] = {};
	uint32_t tex[STAGE_TITLE_NAME] = {};

};


