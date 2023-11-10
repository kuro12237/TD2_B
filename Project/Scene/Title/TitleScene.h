#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"GameObject/SceneChange/SceneChange.h"

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

};
