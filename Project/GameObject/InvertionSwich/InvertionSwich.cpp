#include "InvertionSwich.h"

static uint32_t Invertion = Right;

void InvertionSwich::Initialize(Vector3 pos)
{
	pos;
	model_ = make_unique<Model>();
	model_->CreateFromObj("InvertionSwich");
	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	worldTransform_.UpdateMatrix();

	FoundationModel_= make_unique <Model>();
	FoundationModel_->CreateFromObj("InvertionSwichFoundation");
	foundationWorldTransform_.Initialize();
	foundationWorldTransform_.translate = pos;
	foundationWorldTransform_.UpdateMatrix();

	SetObjectId(0b00010);

	SetCollosionAttribute(kCollisionAttributeInvertionSwich);
	SetCollisionMask(kCollisionMaskInvertionSwich);
	Invertion = Right;

}

void InvertionSwich::Update()
{
	if (!isHit_ && OffsideManager::GetDirection() == Left)
	{
		Invertion = Right;
	}

	if (callbackCollisions && !prevcallBackCollision)
	{
		
		if (isHit_ && OffsideManager::GetDirection() == Right)
		{

			Invertion = Left;
		}
	}
	//isHit_ = false;
	if (Invertion == Left)
	{
		worldTransform_.scale = { 1,1,1 };
	}
	if (Invertion == Right)
	{
	    worldTransform_.scale = { 1,0.2f,1 };
	}

	OffsideManager::SetDirection(Invertion);
	worldTransform_.UpdateMatrix();
	foundationWorldTransform_.UpdateMatrix();
}

void InvertionSwich::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
	FoundationModel_->Draw(foundationWorldTransform_, view);
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
	isHit_ = false;
}

