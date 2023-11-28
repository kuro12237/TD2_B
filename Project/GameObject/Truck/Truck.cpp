#include "Truck.h"

void Truck::Initialize()
{
	bodyModel_ = make_unique<Model>();
	bodyModel_->CreateFromObj("TruckBody");
	bodyWorldTransform_.Initialize();
	bodyWorldTransform_.translate = { -20,0,24 };
	bodyWorldTransform_.scale = { 0.5f,0.5f,0.5f };
	bodyWorldTransform_.UpdateMatrix();

	for (int i = 0; i < 4; i++)
	{
		leftModel_[i] = make_unique<Model>();
		leftModel_[i]->CreateFromObj("TruckWheel");

		leftWorldTransform_[i].Initialize();
		
		leftWorldTransform_[i].parent = &bodyWorldTransform_;
		leftWorldTransform_[i].scale = { 0.7f,0.7f,1.0f };
		leftWorldTransform_[i].translate.y += 0.6f;
		leftWorldTransform_[i].translate.z -= 1.9f;
		leftWorldTransform_[i].UpdateMatrix();

		RightModel_[i] = make_unique<Model>();
		RightModel_[i]->CreateFromObj("TruckWheel");
		
		RightWorldTransform_[i].Initialize();
		
		RightWorldTransform_[i].parent = &bodyWorldTransform_;
		RightWorldTransform_[i].scale = { 0.7f,0.7f,1.0f };
		RightWorldTransform_[i].translate.y += 0.6f;
		RightWorldTransform_[i].translate.z += 1.9f;
		RightWorldTransform_[i].UpdateMatrix();
	}

	leftWorldTransform_[0].translate.x += 6.0f;
	leftWorldTransform_[0].translate.z += 0.2f;
	leftWorldTransform_[0].scale = {0.6f,0.6f,1.0f};

	leftWorldTransform_[1].translate.x += 4.0f;
	leftWorldTransform_[2].translate.x -= 2.0f;
	leftWorldTransform_[3].translate.x -= 4.0f;


	RightWorldTransform_[0].translate.x += 6.0f;
	RightWorldTransform_[0].translate.z -= 0.2f;
	RightWorldTransform_[0].scale = { 0.6f,0.6f,1.0f };

	RightWorldTransform_[1].translate.x += 4.0f;
	RightWorldTransform_[2].translate.x -= 2.0f;
	RightWorldTransform_[3].translate.x -= 4.0f;

}

void Truck::Update()
{
	if (bodyWorldTransform_.translate.x >= 40)
	{
		isAlive = false;
	}

	bodyWorldTransform_.translate.x += 0.1f;
	bodyWorldTransform_.UpdateMatrix();

	for (int i = 0; i < 4; i++)
	{
		leftWorldTransform_[i].rotation.z++;
		leftWorldTransform_[i].UpdateMatrix();

		RightWorldTransform_[i].rotation.z++;
		RightWorldTransform_[i].UpdateMatrix();
	}
}

void Truck::Draw(ViewProjection view)
{
	for (int i = 0; i < 4; i++)
	{
		leftModel_[i]->Draw(leftWorldTransform_[i], view);
		RightModel_[i]->Draw(RightWorldTransform_[i], view);
	}
	bodyModel_->Draw(bodyWorldTransform_, view);
}
