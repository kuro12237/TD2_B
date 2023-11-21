#include "Buggage.h"


static bool isBuggageSelect = false;

void Buggage::Initialize(Vector3 position, uint32_t Attubte, uint32_t Mask)
{
	model_ = make_unique<Model>();
	//uint32_t tex = TextureManager::LoadTexture("Resources/uvChecker.png");
	//model_->SetTexHandle(tex);
	model_->CreateFromObj("Luggage");
	worldTransform_.Initialize();
	worldTransform_.translate = position;
	worldTransform_.UpdateMatrix();

	SetCollosionAttribute(Attubte);
	SetCollisionMask(Mask);
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
	
	if (isHit_)
	{
		SelectBox();
	}

	if (isSelect)
	{
		if (Input::PushKeyPressed(DIK_J))
		{

			array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map = MapManager::GetNowMapTip();

			//マップチップ反転Y
			for (int i = 0; i < MapTip_MAX_Y; i++)
			{
				for (int j = 0; j < MapTip_MAX_X; j++)
				{
					i,j;
					map[MapTip_MAX_Y - i - 1][j] = MapManager::GetNowMapTip()[i][j];
				}
			}
			//右
			if (map[(int)(playerPos_.y)][(int)(playerPos_.x)+2] == AIR)
			{
				worldTransform_.translate = playerPos_;
				worldTransform_.translate.x += 1;

				isHitWall = false;
				isBuggageSelect = false;
				isSelect = false;
				model_->SetColor({ 1,1,1,1 });
			}
		}
	}

	velocity_.y = velocity_.y + gravity;

	Vector2 v{};
	v.x = velocity_.x;
	v.y = velocity_.y;

	SetVelocity(v);
	SetBoxVelocity(velocity_);
	SetRadious(0.5f);

}

void Buggage::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}

void Buggage::Move()
{
	
	isHit_ = false;
	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);
	worldTransform_.UpdateMatrix();
}

void Buggage::SetPlayerVelocity(Vector3 v)
{
	if (isHit_)
	{
		playerVelocity_ = v;
	}
}


void Buggage::RightCollision()
{
	velocity_.x = 0;
	playerVelocity_.x = 0;
	isHitWall = true;
};

void Buggage::LeftCollision()
{
   velocity_.x = 0; 
   playerVelocity_.x = 0;
   isHitWall = true;
}

void Buggage::TopCollision()
{
	velocity_.y = 0;
	playerVelocity_.y = 0;
	//isHitWall = false;
};
void Buggage::DownCollision()
{
	velocity_.y = 0;
	playerVelocity_.y = 0;
	//isHitWall = false;

};

void Buggage::OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	isHit_ = true;
	velocity;
	position;
	overlap;


}

void Buggage::OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{

	overlap, position, velocity;
	if ( !isHitWall)
	{
		velocity_.x += overlap.x;
	}
	
	if (isHitWall)
	{
		velocity_.x = 0;
		//isHitWall = false;
	}

}

void Buggage::OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{
	overlap, position, velocity;
	
	if (!isHitWall)
	{
		velocity_.x -= overlap.x;
	}
	
	if (isHitWall)
	{
		velocity_.x = 0;
		//isHitWall = false;
	}

}

void Buggage::OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{

	overlap, position, velocity;

}

void Buggage::OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity)
{

	overlap, position, velocity;

}

void Buggage::SelectBox()
{
	if (!isSelect&&!isBuggageSelect)
	{
		if (Input::PushKeyPressed(DIK_G))
		{
			isBuggageSelect = true;
			isSelect = true;
			model_->SetColor({ 1,0,0,1 });
		}
	}
}
