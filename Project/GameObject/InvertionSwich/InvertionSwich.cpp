#include "InvertionSwich.h"

static uint32_t Invertion = Right;

void InvertionSwich::Initialize(Vector3 pos)
{
	pos;
	model_ = make_unique<Model>();
	model_->CreateFromObj("TestBox");
	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	worldTransform_.UpdateMatrix();
	SetObjectId(0b00010);

	SetCollosionAttribute(kCollisionAttributeInvertionSwich);
	SetCollisionMask(kCollisionMaskInvertionSwich);
	Invertion = Right;

}

void InvertionSwich::Update()
{
	if (callbackCollisions && !prevcallBackCollision)
	{
		if (isHit_ && OffsideManager::GetDirection() == Right)
		{
			Invertion = Left;
		}
		if (isHit_ && OffsideManager::GetDirection() == Left)
		{
			Invertion = Right;
		}
		isHit_ = false;
	}
	OffsideManager::SetDirection(Invertion);
	worldTransform_.UpdateMatrix();
}

void InvertionSwich::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}

void InvertionSwich::OnCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	isHit_ = true;
	
	callbackCollisions = true;
	LogManager::Log("swich\n");
	overlap, position, velocity,id;
}

void InvertionSwich::OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	overlap, position, velocity,id;
}

void InvertionSwich::OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	overlap, position, velocity,id;
}

void InvertionSwich::OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	overlap, position, velocity,id;
}

void InvertionSwich::OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id)
{
	overlap, position, velocity,id;
}

void InvertionSwich::Reset()
{
	prevcallBackCollision = callbackCollisions;
	callbackCollisions = false;
	
}

