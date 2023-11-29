#include "SelectScene.h"

void SelectScene::Initialize()
{
	int Width = 0;
	int Height = 0;

	model_[0] = make_unique<Sprite>();
	uint32_t tex = TextureManager::LoadTexture("Resources/SelectTex/SelectNumber.png");
	model_[0]->SetTexHandle(tex);
	model_[0]->Initialize(new SpriteBoxState, { 0,0 }, { 128,128 });
	model_[0]->SetSrc({ 0.8f,0.8f }, { 0.8f,1.0f }, { 0.6f,0.8f },{0.6f,1.0f});

	Audiohandle_ = AudioManager::SoundLoadWave("Resources/sounds/Choice.wav");
	Audiohandle_2 = AudioManager::SoundLoadWave("Resources/sounds/Decision.wav");

	worldTransform_[0].Initialize();
	worldTransform_[0].translate.x += 128.0f;
	worldTransform_[0].translate.y += 128.0f;
	worldTransform_[0].UpdateMatrix();

	SelectParam_[0].IsSelect = false;

	for (int i = 1; i < STAGE_MAX; i++)
	{
		model_[i] = make_unique<Sprite>();
		//uint32_t tex = TextureManager::LoadTexture("Resources/SelectTex/SelectNumber.png");
		model_[i]->SetTexHandle(tex);
		model_[i]->Initialize(new SpriteBoxState,{0,0},{128,128});
		model_[i]->SetSrc(
			{ 0.20f+(Height*0.20f), 0.0f + (Width * 0.20f) }, 
			{0.20f + (Height * 0.20f), 0.20f + (Width * 0.20f) },
			{0 + (Height * 0.20f), 0 + (Width * 0.20f) },
			{0 + (Height * 0.20f), 0.20f + (Width * 0.20f) });


		worldTransform_[i].Initialize();
		worldTransform_[i].translate.x += (Height * 128 + 320 +32 * Height);
		worldTransform_[i].translate.y += (Width * 128 + 128 + 10 * Width);
		worldTransform_[i].UpdateMatrix();

		SelectParam_[i].IsSelect = false;
		Height++;
		if ((i)%5==0)
		{
			Width++;
			Height = 0;
		}
	}
	SelectNumber = 0;

	pushASprite_ = make_unique<Sprite>();
	tex = TextureManager::LoadTexture("Resources/PushATex.png");
	pushASprite_->SetTexHandle(tex);
	pushASprite_->Initialize(new SpriteBoxState, { 0,0 }, { 1280, 720 });

	pushAWorldTransform_.Initialize();
	pushAWorldTransform_.scale = { 0.25f,0.25f,1.0f };
	pushAWorldTransform_.translate = { 960,640,0 };
	pushAWorldTransform_.UpdateMatrix();

	viewProjection_.translation_ = { 40,3.0f,18.0f };
	viewProjection_.rotation_ = { 0,-1.3f,0 };
	viewProjection_.UpdateMatrix();
}

void SelectScene::Update(GameManager* Scene)
{
	Scene;
	for (int i = 0; i < STAGE_MAX; i++)
	{
		SelectParam_[i].IsSelect = false;
		model_[i]->SetColor({ 1,1,1,1 });
		worldTransform_[i].scale = { 1,1,1 };
	}

	Contorol();


	SelectParam_[SelectNumber].IsSelect = true;
	worldTransform_[SelectNumber].scale = { 1.2f,1.2f,1.0f };

	for (int i = 0; i < STAGE_MAX; i++)
	{
		worldTransform_[i].UpdateMatrix();
	}
	SkyBox::Update();
	Ground::Update();
	TruckManager::Update();

	pushAWorldTransform_.UpdateMatrix();

	viewProjection_.UpdateMatrix();
	if (SelectNumber==0)
	{
		if (SceneChange::GetScenChangeFlag())
		{
			Scene->ChangeState(new Tutorial01Scene);
			return;
		}
	}

	if (SceneChange::GetScenChangeFlag())
	{
		MapManager::SetSelectMap(SelectNumber);
		Scene->ChangeState(new GameScene);

		return;
	}
	//0
	XINPUT_STATE joyState{};
	Input::NoneJoyState(joyState);
	if (!SelectLock&& Input::GetInstance()->GetJoystickState(joyState) && SceneChange::GetEndChandeFlag())
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			AudioManager::AudioPlayWave(Audiohandle_2);
			SceneChange::ChangeStart();
			SelectLock = true;
		}
	}
	
	//keybord
	if (!SelectLock && SceneChange::GetEndChandeFlag())
	{
		if (Input::PushKeyPressed(DIK_SPACE))
		{
			AudioManager::AudioPlayWave(Audiohandle_2);
			SceneChange::ChangeStart();
			SelectLock = true;
		}
	}
	
}

void SelectScene::Back2dSpriteDraw()
{
}

void SelectScene::Object3dDraw()
{
	
	TruckManager::Draw(viewProjection_);
	SkyBox::Draw(viewProjection_);
	Ground::Draw(viewProjection_);
	
}

void SelectScene::Flont2dSpriteDraw()
{

	for (int i = 0; i < STAGE_MAX; i++)
	{
		model_[i]->Draw(worldTransform_[i]);
	}
	pushASprite_->Draw(pushAWorldTransform_);
}

void SelectScene::Contorol()
{
	if (!SelectLock)
	{
		if (Input::PushKeyPressed(DIK_LEFT) && SelectNumber - 1 >= 0)
		{
			AudioManager::AudioPlayWave(Audiohandle_);
			SelectNumber--;
		}
		if (Input::PushKeyPressed(DIK_RIGHT) && SelectNumber + 1 < STAGE_MAX)
		{
			AudioManager::AudioPlayWave(Audiohandle_);
			SelectNumber++;
		}

		if (Input::PushKeyPressed(DIK_UP) && SelectNumber - 5 >= 0)
		{
			AudioManager::AudioPlayWave(Audiohandle_);
			SelectNumber -= 5;
		}

		if (Input::PushKeyPressed(DIK_DOWN) && SelectNumber + 5 < STAGE_MAX)
		{
			AudioManager::AudioPlayWave(Audiohandle_);
			SelectNumber += 5;
			
		}
		//pad
		XINPUT_STATE joyState{};
		selectTimer_++;
		Input::NoneJoyState(joyState);

		if (Input::GetInstance()->GetJoystickState(joyState)&&selectTimer_ >= 10)
		{
			float x = (float)joyState.Gamepad.sThumbLX / SHRT_MAX;
			float y = (float)joyState.Gamepad.sThumbLY / SHRT_MAX;
			if (x > 0.5f)
			{
				if (SelectNumber + 1 < STAGE_MAX)
				{
					AudioManager::AudioPlayWave(Audiohandle_);
					SelectNumber++;
					selectTimer_ = 0;
				}
			}

			if(x < -0.5f)
			{
				if (SelectNumber - 1 >= 0)
				{
					AudioManager::AudioPlayWave(Audiohandle_);
					SelectNumber--;
					selectTimer_ = 0;
				}
			}

			if (y>0.5f)
			{
				if (SelectNumber - 5 >= 0)
				{
					AudioManager::AudioPlayWave(Audiohandle_);
					SelectNumber -= 5;
					selectTimer_ = 0;
				}

			}

			if (y<-0.5f)
			{
				if (SelectNumber + 5 < STAGE_MAX)
				{
					AudioManager::AudioPlayWave(Audiohandle_);
					SelectNumber += 5;
					selectTimer_ = 0;

				}
			}
		}
	}

}

void SelectScene::stage0_10(GameManager* Scene)
{
	Scene;

	

}
