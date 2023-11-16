#include "SlectScene.h"

SlectScene* SlectScene::GetInstance()
{
	static SlectScene instance;
	return &instance;
}

void SlectScene::Initilize()
{
	uint32_t tex =
		TextureManager::LoadTexture("Resources/uvChecker.png");
	SlectScene::GetInstance()->texHandle= tex;

	for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
	{
		SlectScene::GetInstance()->sprite_[i] = make_unique<Sprite>();
		SlectScene::GetInstance()->sprite_[i]->SetTexHandle(tex);
		SlectScene::GetInstance()->sprite_[i]->Initialize(new SpriteBoxState, { 0,0 }, { 128,128 });
	}

	int width = 1;
	int hegth = 1;

}

void SlectScene::Updata()
{
	for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
	{
		SlectScene::GetInstance()->DrawFlag = true;
	}

}

void SlectScene::Draw()
{
	if (SlectScene::GetInstance()->DrawFlag)
	{
		for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
		{
			SlectScene::GetInstance()->worldTransform_[i].UpdateMatrix();
			SlectScene::GetInstance()->sprite_[i]->Draw(SlectScene::GetInstance()->worldTransform_[i]);
		}
	}

}
