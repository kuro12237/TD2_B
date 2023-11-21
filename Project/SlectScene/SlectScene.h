#pragma once
#include"Sprite/Sprite.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"VectorTransform.h"
#include"IScene.h"
#include"GameObject/SceneChange/SceneChange.h"

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

	unique_ptr<Sprite>sprite_ = {};

	bool DrawFlag = false;

	bool isUpdate = false;

	ViewProjection view{};

	WorldTransform worldTransform_{};

	bool SceneChangeFlag = false;
};
