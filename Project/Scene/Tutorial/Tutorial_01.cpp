#include "Tutorial_01.h"

void Tutorial01Scene::Initialize()
{
	viewProjection_.Initialize();
	viewProjection_.translation_.x = 7;
	viewProjection_.translation_.y = 7;
	viewProjection_.translation_.z = -39;
	viewProjection_.UpdateMatrix();
}

void Tutorial01Scene::Update(GameManager* Scene)
{
	Scene;
	XINPUT_STATE joyState{};
	if (SceneChange::GetScenChangeFlag())
	{
		Scene->ChangeState(new TitleScene);
		return;
	}
	Input::NoneJoyState(joyState);
	if (Input::GetInstance()->GetJoystickState(joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			
			SceneChange::ChangeStart();
		}
	}

	SkyBox::Update();
	Ground::Update();
	TruckManager::Update();
	viewProjection_.UpdateMatrix();
}

void Tutorial01Scene::Back2dSpriteDraw()
{
}

void Tutorial01Scene::Object3dDraw()
{
}

void Tutorial01Scene::Flont2dSpriteDraw()
{
	TruckManager::Draw(viewProjection_);

	SkyBox::Draw(viewProjection_);
	Ground::Draw(viewProjection_);

}
