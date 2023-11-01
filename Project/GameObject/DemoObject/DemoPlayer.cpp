#include"DemoPlayer.h"

void DemoPlayer::Initialize()
{
	worldTransform_.Initialize();
	worldTransform_.translate.y = 1;
	worldTransform_.UpdateMatrix();

	model_ = make_unique<Model>();
	model_->UseLight(HARF_LAMBERT);
	model_->Initialize(new ModelSphereState);
	texHandle_ = TextureManager::LoadTexture("Resources/uvChecker.png");
	model_->SetTexHandle(texHandle_);
	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionAttributeEnemy);
}

void DemoPlayer::Update()
{
	model_->SetColor({ 1,1,1,1 });

	keyControl();
	JoyControl();
	for (shared_ptr<DemoPlayerBullet>& bullet : bullets_)
	{
		bullet->Update();
	}
	worldTransform_.UpdateMatrix();
}

void DemoPlayer::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
	for (shared_ptr<DemoPlayerBullet>& bullet : bullets_)
	{
		bullet->Darw(view);
	}
}

Vector3 DemoPlayer::GetWorldPosition()
{
	Vector3 result{};
	result.x = worldTransform_.matWorld.m[3][0];
	result.y = worldTransform_.matWorld.m[3][1];
	result.z = worldTransform_.matWorld.m[3][2];
	return result;
}

void DemoPlayer::OnCollision()
{
	model_->SetColor({ 1,0,0,1 });
}

void DemoPlayer::keyControl()
{
	if (Input::GetInstance()->PushKey(DIK_W))
	{
		worldTransform_.translate.z += 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_S))
	{
		worldTransform_.translate.z -= 0.1f;
	}

	if (Input::GetInstance()->PushKey(DIK_A))
	{
		worldTransform_.translate.x -= 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_D))
	{
		worldTransform_.translate.x += 0.1f;
	}
	if (Input::GetInstance()->PushKeyPressed(DIK_SPACE))
	{
		shared_ptr<DemoPlayerBullet>bullet = make_shared<DemoPlayerBullet>();
		bullet->Initialize(worldTransform_.translate);
		bullets_.push_back(bullet);
	}

}

void DemoPlayer::JoyControl()
{
	XINPUT_STATE joyState{};
	//«•K‚¸“ü‚ê‚é
	Input::NoneJoyState(joyState);
	if (Input::GetInstance()->GetJoystickState(joyState))
	{
		worldTransform_.translate.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * 0.05f;
		worldTransform_.translate.z += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * 0.05f;	

		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			shared_ptr<DemoPlayerBullet>bullet = make_shared<DemoPlayerBullet>();
			bullet->Initialize(worldTransform_.translate);
			bullets_.push_back(bullet);
		}
	}

}
