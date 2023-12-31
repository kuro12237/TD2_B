#include "TitleScene.h"

void TitleScene::Initialize()
{
	WinApp::SetTiTleName(L"2224_オフサイド運送株式会社");

	DebugCamera* Camera;
	Camera = new DebugCamera();
	Camera->Initialize();
	DebugTools::addCommand(Camera, "f");

	LogManager::Log(SceneName + "\n");

	Audiohandle_ = AudioManager::SoundLoadWave("Resources/sounds/Decision.wav");

	titleSprite_ = make_unique<Sprite>();
	uint32_t tex = TextureManager::LoadTexture("Resources/OffSideLogisticsLogo.png");
	titleSprite_->SetTexHandle(tex);
	titleSprite_->Initialize(new SpriteBoxState, { 0,0 }, { 1223, 285 });
	
	titleWorldTransform_.Initialize();
	titleWorldTransform_.scale = { 0.8f,0.8f,1.0f };
	titleWorldTransform_.translate = { 640,240,0 };
	titleWorldTransform_.UpdateMatrix();

	house_ = make_unique<House>();
	house_->Initialize({ 0,0,32 },{1,1,1});

	view.Initialize();
	view.translation_ = { 0,4,-10 };
	
	view.UpdateMatrix();

	pushASprite_ = make_unique<Sprite>();
	tex = TextureManager::LoadTexture("Resources/Buttons/TitleButtons/TitleButtonA.png");
	pushASprite_->SetTexHandle(tex);
	pushASprite_->Initialize(new SpriteBoxState, { 0,0 }, { 331, 152 });

	pushAWorldTransform_.Initialize();
	pushAWorldTransform_.scale = { 0.4f,0.4f,1.0f };
	pushAWorldTransform_.translate = { 640,640,0 };
	pushAWorldTransform_.UpdateMatrix();

	
}

void TitleScene::Update(GameManager* Scene)
{
	/*if (ImGui::TreeNode("Scene"))
	{

		bool flag = false;
		ImGui::SliderFloat3("uvS", &uvScele_.x, -2.0f, 2.0f);

		if (ImGui::Checkbox("changeSecne", &flag))
		{

		}
		ImGui::TreePop();
	}*/

	//titleWorldTransform_.scale = uvScele_;
	if (SceneChange::GetScenChangeFlag())
	{
		AudioManager::AudioPlayWave(Audiohandle_);
		Scene->ChangeState(new SelectScene);
		return;
	}
	XINPUT_STATE joyState{};
	Input::NoneJoyState(joyState);
	if (Input::GetInstance()->GetJoystickState(joyState) && !SceneChange::GetScenChangeFlag())
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			SceneChange::ChangeStart();
	    }
    }

	if (Input::PushKeyPressed(DIK_SPACE) && !SceneChange::GetScenChangeFlag())
	{
		SceneChange::ChangeStart();
	}




	SkyBox::Update();
	Ground::Update();
	TruckManager::Update();
	titleWorldTransform_.UpdateMatrix();
	pushAWorldTransform_.UpdateMatrix();

	view.UpdateMatrix();

}

void TitleScene::Back2dSpriteDraw()
{

}

void TitleScene::Object3dDraw()
{
	
	TruckManager::Draw(view);

	SkyBox::Draw(view);
	Ground::Draw(view);
}

void TitleScene::Flont2dSpriteDraw()
{
	titleSprite_->Draw(titleWorldTransform_);
	pushASprite_->Draw(pushAWorldTransform_);
}
