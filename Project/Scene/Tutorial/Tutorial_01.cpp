#include "Tutorial_01.h"

void Tutorial01Scene::Initialize()
{
	viewProjection_.Initialize();
	viewProjection_.translation_.x = 7;
	viewProjection_.translation_.y = 7;
	viewProjection_.translation_.z = -39;
	viewProjection_.UpdateMatrix();

	pushASprite_ = make_unique<Sprite>();
	uint32_t tex = TextureManager::LoadTexture("Resources/Buttons/TitleButtons/TitleButtonA.png");
	pushASprite_->SetTexHandle(tex);
	pushASprite_->Initialize(new SpriteBoxState, { 0,0 }, { 331, 152 });

	pushAWorldTransform_.Initialize();
	pushAWorldTransform_.scale = { 0.6f,0.6f,1.0f };
	pushAWorldTransform_.translate = { 640,520,0 };
	pushAWorldTransform_.UpdateMatrix();

	tex = TextureManager::LoadTexture("Resources/Tutorial/TutorialRule.png");
	Audiohandle_ = AudioManager::SoundLoadWave("Resources/sounds/Decision.wav");
	explainSprite_ = make_unique<Sprite>();
	explainSprite_->SetTexHandle(tex);
	explainSprite_->Initialize(new SpriteBoxState, { 0,0 }, { 1280,720 });

	explainWorldTransform.Initialize();
	explainWorldTransform.scale = { 0.8f,0.8f,0.8f };
	explainWorldTransform.translate = { 640,360,0 };
	explainWorldTransform.UpdateMatrix();
}

void Tutorial01Scene::Update(GameManager* Scene)
{
	Scene;
	XINPUT_STATE joyState{};

	if (SceneChange::GetScenChangeFlag())
	{
		Scene->ChangeState(new SelectScene);
		return;
	}

	Input::NoneJoyState(joyState);
	if (Input::GetInstance()->GetJoystickState(joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			SceneChange::ChangeStart();
			this->time_++;

			if (this->time_ > 5)
			{
				this->isPlayingAudio_ = true;
			}

			if (isPlayingAudio_)
			{
				AudioManager::AudioPlayWave(Audiohandle_);
				this->isPlayingAudio_ = false;
				this->time_ = 0;
			}
			
		}
	}

	SkyBox::Update();
	Ground::Update();
	TruckManager::Update();
	explainWorldTransform.UpdateMatrix();
	pushAWorldTransform_.UpdateMatrix();
	viewProjection_.UpdateMatrix();
}

void Tutorial01Scene::Back2dSpriteDraw()
{
}

void Tutorial01Scene::Object3dDraw()
{
	TruckManager::Draw(viewProjection_);

	SkyBox::Draw(viewProjection_);
	Ground::Draw(viewProjection_);
}

void Tutorial01Scene::Flont2dSpriteDraw()
{
	explainSprite_->Draw(explainWorldTransform);
	pushASprite_->Draw(pushAWorldTransform_);
}
