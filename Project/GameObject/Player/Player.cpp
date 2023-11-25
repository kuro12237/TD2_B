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
	
	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	worldTransform_.scale = { 0.2f,0.2f,0.2f };
	worldTransform_.rotation = { 0.0f,-2.0f,0.0f };
	worldTransform_.UpdateMatrix();
	//model_->SetColor({ 0,0,1,1 });

	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionMaskPlayer);
	//Select用
	for (int i = 0; i < SELECT_MODEL_MAX; i++)
	{
		SelectModel_[i] = make_unique<Model>();
		SelectModel_[i]->CreateFromObj("SelectModel");
		SelectWorldTransform[i].Initialize();
		SelectWorldTransform[i].scale = { 0.5f,0.5f,1 };

	
	}
	
	SelectWorldTransform[0].UpdateMatrix();
	SelectWorldTransform[1].UpdateMatrix();
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
	
	
	if (Input::PushKey(DIK_A))
	{
		velocity_.x = -speed;
		worldTransform_.rotation.y = 2.0f;
	}
	else if (Input::PushKey(DIK_D))
	{
		velocity_.x = speed;
		worldTransform_.rotation.y = -2.0f;
	}

	if (nowMapPos_ != LADER)
	{
		if (Input::PushKeyPressed(DIK_SPACE) && !isJamp)
		{
			JampFrame = 0;
			jampVelocity = { 0,0.0f };
			isJamp = true;
		}
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

	SelectWorldTransform[0].translate = worldTransform_.translate;
	SelectWorldTransform[0].translate.x = worldTransform_.translate.x-1;

	SelectWorldTransform[1].translate = worldTransform_.translate;
	SelectWorldTransform[1].translate.x = worldTransform_.translate.x+1;


	SelectWorldTransform[0].UpdateMatrix();
	SelectWorldTransform[1].UpdateMatrix();

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
		for (int i = 0; i < SELECT_MODEL_MAX; i++)
		{
			SelectModel_[i]->Draw(SelectWorldTransform[i], view);
		}
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
	isHit_ = true;
	//isJamp = false;
	position, velocity;
	overlap;
	id;

	//velocity_.y += overlap.y;
}

void Player::OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap, position, velocity;
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

void Player::OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{

	overlap, position, velocity;
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



void Player::OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{

	overlap, position, velocity;
	
	
	velocity_.y += overlap.y;
	
	if (velocity_.y < 0.0f)
	{
		isJamp = false;
	}
	LogManager::Log("TopHit\n");
	

}

void Player::OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	velocity_.y -= overlap.y;
	overlap, position, velocity;

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
	if (Input::PushKeyPressed(DIK_G))
	{
		if (isHit_)
		{
			isBuggagesSelect = true;
		}
	}
	//切り替え
	if (Input::PushKeyPressed(DIK_LEFT))
	{
		BuggageSelectDirection=Left;
	}
	
	if (Input::PushKeyPressed(DIK_RIGHT))
	{
		BuggageSelectDirection = Right;
	}

	for (int i = 0; i < 2; i++)
	{
		SelectModel_[i]->SetColor({ 1,1,1,1 });
	}
	if (BuggageSelectDirection == Left)
	{
		SelectModel_[0]->SetColor({ 1,0,0,1 });
	}
	if (BuggageSelectDirection == Right)
	{
		SelectModel_[1]->SetColor({ 1,0,0,1 });
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

	if (OffsideManager::GetDirection() == Right)
	{
		if (Input::PushKeyPressed(DIK_J) && worldTransform_.translate.x <= OffsideManager::GetOffsidePos().x)
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

	if (OffsideManager::GetDirection() == Left)
	{
		if (Input::PushKeyPressed(DIK_J) && worldTransform_.translate.x >= OffsideManager::GetOffsidePos().x)
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
