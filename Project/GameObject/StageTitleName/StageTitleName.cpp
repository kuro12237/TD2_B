#include "StageTitleName.h"

StageTitleName* StageTitleName::GetInstance()
{
	static StageTitleName instance;
	return &instance;
}

void StageTitleName::Initialize()
{
	LoadTexs();


	StageTitleName::GetInstance()->sprites_ = make_unique<Sprite>();
	StageTitleName::GetInstance()->sprites_->SetTexHandle(StageTitleName::GetInstance()->tex[0]);
	StageTitleName::GetInstance()->sprites_->Initialize(new SpriteBoxState, { 0,0 }, { 1548.0f,228.0f });
	StageTitleName::GetInstance()->worldTransform.Initialize();
	StageTitleName::GetInstance()->worldTransform.translate = { 1548/4,228/4,1 };
	StageTitleName::GetInstance()->worldTransform.scale = { 0.5f,0.5f,0.5f };
	StageTitleName::GetInstance()->worldTransform.UpdateMatrix();


	for (int i = 0; i < STAGE_TITLE_NAME; i++)
	{
		StageTitleName::GetInstance()->isPrintFlag_[i] = false;
	}

}

void StageTitleName::Update()
{
	uint32_t NowMapNumber = MapManager::GetNowStageNumber();

	if (NowMapNumber<= 10)
	{
		StageTitleName::GetInstance()->isPrintFlag_[NowMapNumber - 1] = true;
		StageTitleName::GetInstance()->sprites_->SetTexHandle(StageTitleName::GetInstance()->tex[NowMapNumber - 1]);
	}

}

void StageTitleName::Draw(ViewProjection view)
{
	for (int i = 0; i < 10; i++)
	{
		if (StageTitleName::GetInstance()->isPrintFlag_[i])
		{
			StageTitleName::GetInstance()->sprites_->Draw(StageTitleName::GetInstance()->worldTransform);
			StageTitleName::GetInstance()->isPrintFlag_[i] = false;
		}
	}
	view;
}

void StageTitleName::LoadTexs()
{
	StageTitleName::GetInstance()->tex[0] = TextureManager::LoadTexture("resources/TutorialTitle/titleStage01.png");
	StageTitleName::GetInstance()->tex[1] = TextureManager::LoadTexture("resources/TutorialTitle/titleStage02.png");
	StageTitleName::GetInstance()->tex[2] = TextureManager::LoadTexture("resources/TutorialTitle/titleStage03.png");
	StageTitleName::GetInstance()->tex[3] = TextureManager::LoadTexture("resources/TutorialTitle/titleStage04.png");
	StageTitleName::GetInstance()->tex[4] = TextureManager::LoadTexture("resources/TutorialTitle/titleStage05.png");

	StageTitleName::GetInstance()->tex[5] = TextureManager::LoadTexture("resources/TutorialTitle/titleStage06.png");
	StageTitleName::GetInstance()->tex[6] = TextureManager::LoadTexture("resources/TutorialTitle/titleStage07.png");
	StageTitleName::GetInstance()->tex[7] = TextureManager::LoadTexture("resources/TutorialTitle/titleStage08.png");
	StageTitleName::GetInstance()->tex[8] = TextureManager::LoadTexture("resources/TutorialTitle/titleStage09.png");
	StageTitleName::GetInstance()->tex[9] = TextureManager::LoadTexture("resources/TutorialTitle/titleStage10.png");

}
