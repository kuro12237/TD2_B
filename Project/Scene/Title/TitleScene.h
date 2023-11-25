#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"GameObject/SceneChange/SceneChange.h"
#include"Model.h"
#include"DebugTools/DebugTools.h"
#include"Scene/SelectScene/SelectScene.h"


class TitleScene : public IScene
{
public:
	TitleScene() {};
	~TitleScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	ViewProjection view{};

	const string SceneName = "TitleScene";
	unique_ptr<Sprite>titleSprite_ = nullptr;
	WorldTransform titleWorldTransform_ = {};
	Vector3 uvScele_ = { 1,1,1 };

};
