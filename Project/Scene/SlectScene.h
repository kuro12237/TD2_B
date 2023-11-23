#pragma once
#include"Sprite/Sprite.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"VectorTransform.h"
#include"IScene.h"
#include"GameObject/SceneChange/SceneChange.h"
#include"MatrixTransform.h"
#include"Input/Input.h"
#include"GameManager/GameManager.h"

#define SLECTSTAGE_SPRITE_MAX 40


class SlectStage :public IScene
{
public:
	SlectStage() {};
	~SlectStage() {};
	void Initialize()override;
	void Update(GameManager* Scene)override;
	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	uint32_t SpritetexHandle = 0;

	uint32_t SlecttexHandle = 0;

	bool DrawFlag = true;

	bool isUpdate = false;

	unique_ptr<Sprite>sprite_[SLECTSTAGE_SPRITE_MAX] = {};
	WorldTransform worldTransform_[SLECTSTAGE_SPRITE_MAX]{};

	unique_ptr<Sprite>Slectsprite_ = nullptr;

	WorldTransform SlectTransform_;

	ViewProjection view{};

	bool isStart_ = false;

	bool isEnd_ = false;

	bool SceneChangeFlag = false;


};

