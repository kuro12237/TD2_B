#include "Player.h"

void Player::Initialize(Vector3 pos)
{
	modelPlayerFace_ = make_unique<Model>();
	modelPlayerFace_->CreateFromObj("PlayerFace");
	modelPlayerBody_ = make_unique<Model>();
	modelPlayerBody_->CreateFromObj("PlayerBody");
	modelPlayerHat_ = make_unique<Model>();
	modelPlayerHat_->CreateFromObj("PlayerHat");
	modelPlayerLeftHand_ = make_unique<Model>();
	modelPlayerLeftHand_->CreateFromObj("PlayerLeft");
	modelPlayerRightHand_ = make_unique<Model>();
	modelPlayerRightHand_->CreateFromObj("PlayerRight");
	
	Audiohandle_ = AudioManager::SoundLoadWave("Resources/sounds/Soilwalk.wav");
	Audiohandle2_ = AudioManager::SoundLoadWave("Resources/sounds/Pushluggage.wav");
	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	worldTransform_.scale = { 0.2f,0.2f,0.2f };
	worldTransform_.rotation = { 0.0f,-2.0f,0.0f };
	worldTransform_.UpdateMatrix();
	

	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionMaskPlayer);
	//Select用

	SelectModel_ = make_unique<Model>();
	SelectModel_->CreateFromObj("SelectModel");
	SelectWorldTransform.Initialize();
	SelectWorldTransform.scale = { 0.5f,0.5f,1 };
	
	
	SelectWorldTransform.UpdateMatrix();
}

void Player::GravityUpdate()
{
	velocity_ = {};
	velocity_.y = velocity_.y + gravity;

}

void Player::Update()
{

	if (ImGui::TreeNode("Player"))
	{
		ImGui::Text("position %f %f %f", worldTransform_.translate.x, worldTransform_.translate.y, worldTransform_.translate.z);
		ImGui::Text("SelectSet key::left,Right ");

		ImGui::SliderFloat("speed", &speed,-1.0f,1.0f);
		ImGui::TreePop();
	}
	
	KeyControl();

	GamePadContorol();

	//向き
	if (velocity_.x > 0)
	{
		BuggageSelectDirection = Right;
		
		worldTransform_.rotation.y = -2.0f;
	}
	if (velocity_.x < 0)
	{
		BuggageSelectDirection = Left;
		worldTransform_.rotation.y = 2.0f;
	}
	
	Jamp();
	SelectBox();
	Vector2 v = { velocity_.x,velocity_.y };

	SetBoxVelocity(velocity_);
	SetVelocity(v);
	SetRadious(0.5f);


}

void Player::Move()
{

	isHit_ = false;
	
	
	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);
	worldTransform_.UpdateMatrix();

	if (BuggageSelectDirection == Left)
	{
		
		SelectWorldTransform.translate = worldTransform_.translate;
		SelectWorldTransform.translate.x = worldTransform_.translate.x - 1;
	}
	if (BuggageSelectDirection == Right)
	{
		SelectWorldTransform.translate = worldTransform_.translate;
		SelectWorldTransform.translate.x = worldTransform_.translate.x + 1;
	}

	SelectWorldTransform.UpdateMatrix();
}

void Player::Draw(ViewProjection view)
{
	modelPlayerFace_->Draw(worldTransform_, view);
	modelPlayerBody_->Draw(worldTransform_, view);
	modelPlayerHat_->Draw(worldTransform_, view);
	modelPlayerLeftHand_->Draw(worldTransform_, view);
	modelPlayerRightHand_->Draw(worldTransform_, view);
	if (isBuggagesSelect)
	{
		
		SelectModel_->Draw(SelectWorldTransform, view);
		
	}
}

void Player::RightCollision(uint32_t nowMapPos)
{
	nowMapPos_ = nowMapPos;
	if (nowMapPos_ != LADER)
	{
		velocity_.x = 0;
	}
}

void Player::LeftCollision(uint32_t nowMapPos)
{
	nowMapPos_ = nowMapPos;
	if (nowMapPos_ != LADER)
	{ 
	    velocity_.x = 0;
    }
}

void Player::TopCollision(uint32_t nowMapPos)
{
	nowMapPos_ = nowMapPos;
	if (nowMapPos_ != LADER)
	{
		velocity_.y = 0;
	}

}

void Player::DownCollision(uint32_t nowMapPos)
{
	nowMapPos_ = nowMapPos;

	if (nowMapPos_ != LADER)
	{
		velocity_.y = 0;
	}

	if (velocity_.y == 0.0f)
	{
		isJamp = false;
	}
}

void Player::OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	
	//isJamp = false;
	position, velocity;
	overlap;
	id;
	if (id==0b00010)
	{
		return;
	}
	isHit_ = true;
	//velocity_.y += overlap.y;
}

void Player::OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	this->time_+=5;

	if (this->time_ > 18)
	{
		this->isPlayingAudio_ = true;
	}

	if (isPlayingAudio_)
	{
		AudioManager::AudioPlayWave(Audiohandle2_);
		this->isPlayingAudio_ = false;
		this->time_ = 0;
	}


	if (id == 0b00010)
	{
		return;
	}
	overlap, position, velocity,id;
	if (overlap.x < 0.0f)
	{
		velocity_.x += overlap.x;
	}
	
	if (velocity.x > 0)
	{	
		velocity_.x = 0;
		return;	
	}

	LogManager::Log("HitLeft!!\n");
}

void Player::OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	this->time_++;

	if (this->time_ > 20)
	{
		this->isPlayingAudio_ = true;
	}

	if (isPlayingAudio_)
	{
		AudioManager::AudioPlayWave(Audiohandle2_);
		this->isPlayingAudio_ = false;
		this->time_ = 0;
	}
	


	if (id == 0b00010)
	{
		return;
	}
	overlap, position, velocity,id;
	if (overlap.x > 0.0f)
	{
		velocity_.x -= overlap.x;
	}
	if (velocity.x > 0)
	{

		//velocity_.x = 0;
		return;

	}
	
		
	LogManager::Log("HitRight!!\n");

}



void Player::OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	if (id == 0b00010)
	{
		return;
	}
	overlap, position, velocity,id;
	
	
	velocity_.y += overlap.y;
	
	if (velocity_.y < 0.0f)
	{
		isJamp = false;
	}
	LogManager::Log("TopHit\n");
	

}

void Player::OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	if (id == 0b00010)
	{
		return;
	}
	velocity_.y -= overlap.y;
	overlap, position, velocity,id;

}

void Player::KeyControl()
{

	if (Input::PushKey(DIK_A))
	{
		AudioManager::AudioPlayWave(Audiohandle_);
		velocity_.x = -speed;
	}
	else if (Input::PushKey(DIK_D))
	{
		AudioManager::AudioPlayWave(Audiohandle_);
		velocity_.x = speed;
	}

	if (Input::PushKeyPressed(DIK_SPACE) && !isJamp)
	{
		JampFrame = 0;
		jampVelocity = { 0,0.0f };
		isJamp = true;
	}
}

void Player::GamePadContorol()
{
	XINPUT_STATE joyState{};
	Input::NoneJoyState(joyState);
	float x = 0;
	if (Input::GetInstance()->GetJoystickState(joyState))
	{
		x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed;
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A && !isJamp)
		{
			JampFrame = 0;
			jampVelocity = { 0,0.0f };
			isJamp = true;
		}
	}
	
	if (x<0.05f && x>-0.05f)
	{
		x = 0;

	}else{
		this->time_++;
	}

	if (this->time_ >18.5)
	{
	  this->isPlayingAudio_ = true;
	}

	if (isPlayingAudio_)
	{
		AudioManager::AudioPlayWave(Audiohandle_);
		this->isPlayingAudio_ = false;
		this->time_ = 0;
	}

	velocity_.x += x;
}

void Player::Jamp()
{
	if (JampFrame < 10)
	{
         velocity_.y += 0.5f;
		JampFrame++;
	}
}

void Player::SelectBox()
{
	//選択
	//切り替え
	if (Input::PushKeyPressed(DIK_LEFT))
	{
		BuggageSelectDirection=Left;
	}
	
	if (Input::PushKeyPressed(DIK_RIGHT))
	{
		BuggageSelectDirection = Right;
	}

	if (isHit_)
	{
		isBuggagesSelect = true;
	}

	array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map = MapManager::GetNowMapTip();

	//マップチップ反転Y
	for (int i = 0; i < MapTip_MAX_Y; i++)
	{
		for (int j = 0; j < MapTip_MAX_X; j++)
		{
			map[MapTip_MAX_Y - i - 1][j] = MapManager::GetNowMapTip()[i][j];
		}
	}

	//設置

	XINPUT_STATE joyState{};
	Input::NoneJoyState(joyState);


	if (OffsideManager::GetDirection() == Right)
	{

		if (Input::PushKeyPressed(DIK_J) || Input::GetInstance()->GetJoystickState(joyState) && joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			if (worldTransform_.translate.x < OffsideManager::GetOffsidePos().x)
			{
			       
			    if (BuggageSelectDirection == Left)
			    {
			    	if (map[(int)(worldTransform_.translate.y)][(int)(worldTransform_.translate.x - 1.3f)] == AIR)
			    	{
			    		isBuggagesSelect = false;
			    	}
			    }
			       
			    if (BuggageSelectDirection == Right)
			    {
			    	if (map[(int)(worldTransform_.translate.y)][(int)(worldTransform_.translate.x + 2.4f)] == AIR)
			    	{
			    		isBuggagesSelect = false;
			    	}
			    }
			       
				
			}
		}
	}
	if (OffsideManager::GetDirection() == Left)
	{
		
		if (Input::PushKeyPressed(DIK_J) || Input::GetInstance()->GetJoystickState(joyState) && joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			if (worldTransform_.translate.x-1 >= OffsideManager::GetOffsidePos().x)
			{
				if (BuggageSelectDirection == Left)
				{
					if (map[(int)(worldTransform_.translate.y)][(int)(worldTransform_.translate.x - 0.8f)] == AIR)
					{
						isBuggagesSelect = false;
					}
				}

				if (BuggageSelectDirection == Right)
				{
					if (map[(int)(worldTransform_.translate.y)][(int)(worldTransform_.translate.x) + 2] == AIR)
					{
						isBuggagesSelect = false;
					}
				}

			}
		}
	}

}
