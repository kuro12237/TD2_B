#include "Buggage.h"


static bool isBuggagesSelect = false;


void Buggage::Initialize(Vector3 position, uint32_t Attubte, uint32_t Mask)
{
	model_ = make_unique<Model>();
	model_->CreateFromObj("Luggage");
	worldTransform_.Initialize();
	worldTransform_.translate = position;
	worldTransform_.UpdateMatrix();

	SetCollosionAttribute(Attubte);
	SetCollisionMask(Mask);
	isBuggagesSelect = false;
}

void Buggage::Update()
{

	if (ImGui::TreeNode("Baggage"))
	{
		ImGui::Text("position %f %f %f", worldTransform_.translate.x, worldTransform_.translate.y, worldTransform_.translate.z);
		ImGui::Text("Velocity %f %f %f", velocity_.x, velocity_.y, velocity_.z);
		
		ImGui::TreePop();
	}
	
	if (ImGui::TreeNode("BaggageSelect"))
	{
		ImGui::Text("G Select");
		ImGui::Text("J warp");
		ImGui::TreePop();
	}
	
	if (!isHit_)
	{
		velocity_.x = 0;
	}
	
	if (isHit_ && isBuggagesSelect)
	{

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

	SetBoxR(map);
	SetBoxL(map);
	velocity_.y = velocity_.y + gravity;

	Vector2 v{};
	v.x = velocity_.x;
	v.y = velocity_.y;

	SetPosition(worldTransform_.translate);
	SetVelocity(v);
	SetVec3Velocity(velocity_);

	SetBoxVelocity(velocity_);
	SetRadious(0.5f);
}

void Buggage::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
	isHitWall = false;
}

void Buggage::Move()
{
	prevHit_ = isHit_;
	isHit_ = false;


	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);
	worldTransform_.UpdateMatrix();

}

bool Buggage::isSelectChange(bool Select)
{
	if (!isHit_&&isBuggagesSelect&&isSelect&&Select)
	{
		isSelect = false;
		return true;
	}

	return false;
}

void Buggage::SetPlayerVelocity(Vector3 v)
{
	if (isHit_)
	{
		playerVelocity_ = v;
	}
}

void Buggage::RightCollision(uint32_t nowMapPos)
{
	nowMapPos;
	velocity_.x = 0;
	playerVelocity_.x = 0;
	isHitWall = true;
};

void Buggage::LeftCollision(uint32_t nowMapPos)
{
	nowMapPos;
   velocity_.x = 0; 
   playerVelocity_.x = 0;
   isHitWall = true;
}

void Buggage::TopCollision(uint32_t nowMapPos)
{
	nowMapPos;
	velocity_.y = 0;
	playerVelocity_.y = 0;
	//isHitWall = false;
};
void Buggage::DownCollision(uint32_t nowMapPos)
{
	nowMapPos;
	velocity_.y = 0;
	playerVelocity_.y = 0;
	//isHitWall = false;

};

void Buggage::SetIsSelect(bool Selecr)
{


	if (Selecr && !isBuggagesSelect&&isHit_)
	{
		isSelect = Selecr;
		isBuggagesSelect = true;
		model_->SetColor({ 1,0,0,1 });
	}
}

void Buggage::OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	if (id == 0b00010)
	{
		return;
	}
	
	isHit_ = true;
	velocity;
	position;
	overlap;
	id;
	if (id==0b0001)
	{
		LogManager::Log("delete\n");
		isAlive_ = false;
		return;
	}
}

void Buggage::OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{

	overlap, position, velocity,id;
	if (id == 0b00010)
	{
		return;
	}
	if ( !isHitWall)
	{
		velocity_.x += (overlap.x);
	}
	
	if (isHitWall)
	{
		velocity_.x = 0;
		//isHitWall = false;
	}

}

void Buggage::OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	overlap, position, velocity,id;
	
	if (id == 0b00010)
	{
		return;
	}
	if (!isHitWall)
	{
		velocity_.x -= (overlap.x);
	}
	
	if (isHitWall)
	{
		velocity_.x = 0;
		//isHitWall = false;
	}

}

void Buggage::OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	id;
	if (id == 0b00010)
	{
		return;
	}
	overlap, position, velocity;

}

void Buggage::OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	id;
	if (id == 0b00010)
	{
		return;
	}
	overlap, position, velocity;

}

void Buggage::SetOpenPortal(Vector3 pos)
{

	pos;
}

void Buggage::ChangeOnSelect()
{
	isSelect = true;
	model_->SetColor({ 1,0,0,1 });
}


void Buggage::ChangeNoneSelect()
{
	isSelect = false;
	model_->SetColor({ 1,1,1,1 });
}


void Buggage::SetBoxR(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map)
{
	if (OffsideManager::GetDirection() == Right)
	{
		if (isSelect && playerPos_.x-1 <= OffsideManager::GetOffsidePos().x)
		{
			XINPUT_STATE joyState{};
			Input::NoneJoyState(joyState);

			if (Input::PushKeyPressed(DIK_J)|| Input::GetInstance()->GetJoystickState(joyState)&& joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				//右
				if (SelectDirection_ == Right)
				{
					if (map[(int)(playerPos_.y)][(int)(playerPos_.x + 2.4f) ] == AIR)
					{
						worldTransform_.translate = playerPos_;
						worldTransform_.translate.x += 1.4f;

						isHitWall = false;
						isBuggagesSelect = false;
						isSelect = false;
						model_->SetColor({ 1,1,1,1 });
						return;
					}
					
				}
				//左
				if (SelectDirection_ == Left)
				{
					if (map[(int)(playerPos_.y)][(int)(playerPos_.x - 1.3f)] == AIR)
					{

						worldTransform_.translate = playerPos_;
						worldTransform_.translate.x -= 1.4f;
						isHitWall = false;
						isBuggagesSelect = false;
						isSelect = false;
						model_->SetColor({ 1,1,1,1 });
						return;

					}
				}
			}
		}
	}
}

void Buggage::SetBoxL(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map)
{
	if (OffsideManager::GetDirection() == Left)
	{
		if (isSelect && playerPos_.x > OffsideManager::GetOffsidePos().x)
		{
			XINPUT_STATE joyState{};
			Input::NoneJoyState(joyState);

			if (Input::PushKeyPressed(DIK_J) || Input::GetInstance()->GetJoystickState(joyState) && joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				//右
				if (SelectDirection_ == Right)
				{
					if (map[(int)(playerPos_.y)][(int)(playerPos_.x) + 2] == AIR)
					{
						worldTransform_.translate = playerPos_;
						worldTransform_.translate.x += 1;

						isHitWall = false;
						isBuggagesSelect = false;
						isSelect = false;
						model_->SetColor({ 1,1,1,1 });
						return;
					}
				}
				//左
				if (SelectDirection_ == Left)
				{
					if (map[(int)(playerPos_.y)][(int)(playerPos_.x - 0.8f)] == AIR)
					{

						worldTransform_.translate = playerPos_;
						worldTransform_.translate.x = playerPos_.x - 1.0f;
						isHitWall = false;
						isBuggagesSelect = false;
						isSelect = false;
						model_->SetColor({ 1,1,1,1 });
						return;

					}
				}
			}
		}
	}
}
