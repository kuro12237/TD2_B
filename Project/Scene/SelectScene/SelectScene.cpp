#include "SelectScene.h"

void SelectScene::Initialize()
{
	int Width = 0;
	int Height = 0;
	for (int i = 0; i < STAGE_MAX; i++)
	{
		model_[i] = make_unique<Sprite>();
		uint32_t tex = TextureManager::LoadTexture("Resources/uvChecker.png");
		model_[i]->SetTexHandle(tex);
		model_[i]->Initialize(new SpriteBoxState,{0,0},{128,128});

		worldTransform_[i].Initialize();
		worldTransform_[i].translate.x += (Height * 128 + 320 +32 * Height);
		worldTransform_[i].translate.y += (Width * 128 + 128 + 10 * Width);
		worldTransform_[i].UpdateMatrix();

		SelectParam_[i].IsSelect = false;
		Height++;
		if ((i+1)%5==0)
		{
			Width++;
			Height = 0;
		}
	}
	SelectNumber = 0;

	viewProjection_.translation_ = { 40,3.0f,-0.0f };
	viewProjection_.rotation_ = { 0,-1.1f,0 };
	viewProjection_.UpdateMatrix();
}

void SelectScene::Update(GameManager* Scene)
{
	Scene;
	for (int i = 0; i < STAGE_MAX; i++)
	{
		SelectParam_[i].IsSelect = false;
		model_[i]->SetColor({ 1,1,1,1 });
	}

	Contorol();


	SelectParam_[SelectNumber].IsSelect = true;
	model_[SelectNumber]->SetColor({ 1,0,0,1 });

	ImGui::Begin("camera");
	ImGui::SliderFloat3("r", &viewProjection_.rotation_.x,-2.0f,2.0f);
	ImGui::End();
	for (int i = 0; i < STAGE_MAX; i++)
	{
		worldTransform_[i].UpdateMatrix();
	}
	SkyBox::Update();
	Ground::Update();
	TruckManager::Update();

	viewProjection_.UpdateMatrix();
	stage0_10(Scene);

	//0
	if (SelectNumber == 0 && !SelectLock)
	{

		if (Input::PushKeyPressed(DIK_SPACE))
		{
			SceneChange::ChangeStart();

		}
	}
	if (SelectNumber == 0)
	{
		if (SceneChange::GetScenChangeFlag())
		{
			Scene->ChangeState(new Stage1Scene);
			return;
		}
	}
}

void SelectScene::Back2dSpriteDraw()
{
}

void SelectScene::Object3dDraw()
{
	if (!SelectLock)
	{
		TruckManager::Draw(viewProjection_);
		SkyBox::Draw(viewProjection_);
		Ground::Draw(viewProjection_);
	}
}

void SelectScene::Flont2dSpriteDraw()
{

	for (int i = 0; i < STAGE_MAX; i++)
	{
		model_[i]->Draw(worldTransform_[i]);
	}
}

void SelectScene::Contorol()
{
	if (!SelectLock)
	{
		if (Input::PushKeyPressed(DIK_LEFT) && SelectNumber - 1 >= 0)
		{
			SelectNumber--;
		}
		if (Input::PushKeyPressed(DIK_RIGHT) && SelectNumber + 1 < STAGE_MAX)
		{
			SelectNumber++;
		}

		if (Input::PushKeyPressed(DIK_UP) && SelectNumber - 5 >= 0)
		{
			SelectNumber -= 5;
		}

		if (Input::PushKeyPressed(DIK_DOWN) && SelectNumber + 5 < STAGE_MAX)
		{
			SelectNumber += 5;
			
		}
	}

}

void SelectScene::stage0_10(GameManager* Scene)
{
	
	Scene;
	
	
}
