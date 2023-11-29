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
	//StageTitleName::GetInstance()->sprites_[i]->Initialize(new SpriteBoxState,{0,0},{})
	StageTitleName::GetInstance()->worldTransform.Initialize();
	for (int i = 0; i < STAGE_TITLE_NAME; i++)
	{
		StageTitleName::GetInstance()->isPrintFlag_[i] = false;
	}

}

void StageTitleName::Update()
{
	uint32_t ifNowMapNumber = MapManager::GetNowStageNumber();



}

void StageTitleName::Draw(ViewProjection view)
{
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
