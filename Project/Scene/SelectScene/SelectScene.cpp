#include "SelectScene.h"

void SelectScene::Initialize()
{
	int Width = 0;
	int Height = 0;

	model_[0] = make_unique<Sprite>();
	uint32_t tex = TextureManager::LoadTexture("Resources/SelectTex/SelectNumber.png");
	model_[0]->SetTexHandle(tex);
	model_[0]->Initialize(new SpriteBoxState, { 0,0 }, { 128*3,128 });
	model_[0]->SetSrc({ 0.60f,0.8f }, { 0.60f,1.00f }, { 0,0.8f }, { 0,1.00f });

	worldTransform_[0].Initialize();
	worldTransform_[0].translate.x += 128.0f;
	worldTransform_[0].translate.y += 360.0f;
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

	ImGui::Begin("camera");
	ImGui::SliderFloat3("r", &viewProjection_.rotation_.x,-2.0f,2.0f);
	ImGui::DragFloat3("t", &viewProjection_.translation_.x, -2.0f, 2.0f);
	ImGui::End();

	Matrix4x4 r = MatrixTransform::RotateZMatrix(float(numbers::pi/2));
	Matrix4x4 t = MatrixTransform::TranslateMatrix(worldTransform_[0].translate);
	Matrix4x4 s = MatrixTransform::ScaleMatrix(worldTransform_[0].scale);

	worldTransform_[0].matWorld = MatrixTransform::Multiply(s ,MatrixTransform::Multiply(r,t));

	for (int i = 1; i < STAGE_MAX; i++)
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
			SceneChange::ChangeStart();
			SelectLock = true;
		}
	}
	
	//keybord
	if (!SelectLock && SceneChange::GetEndChandeFlag())
	{
		if (Input::PushKeyPressed(DIK_SPACE))
		{
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
		//pad
		XINPUT_STATE joyState{};
		selectTimer_++;
		Input::NoneJoyState(joyState);

		if (Input::GetInstance()->GetJoystickState(joyState)&&selectTimer_>=10)
		{
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
			{
				if (SelectNumber - 1 >= 0)
				{
					SelectNumber--;
					selectTimer_ = 0;
				}
			}

			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				if(SelectNumber + 1 < STAGE_MAX)
				{
					SelectNumber++;
					selectTimer_ = 0;
				}
			}
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
			{
			
					if (SelectNumber - 5 >= 0)
					{
						SelectNumber -= 5;
						selectTimer_ = 0;
					}
				
			}
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{
				if (SelectNumber  + 5 < STAGE_MAX) 
				{
					
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
