#include "SkyBox.h"

SkyBox* SkyBox::GetInstance()
{
	static SkyBox instance;
	return &instance;
}

void SkyBox::Initialize()
{
	if (!SkyBox::GetInstance()->InitializeLock)
	{
		SkyBox::GetInstance()->model_ = make_unique<Model>();
		SkyBox::GetInstance()->model_->CreateFromObj("SkyBox");

		SkyBox::GetInstance()->worldTransform_.Initialize();
		const float scaleMax = 64;
		SkyBox::GetInstance()->worldTransform_.scale = { scaleMax,scaleMax,scaleMax  };
		SkyBox::GetInstance()->worldTransform_.UpdateMatrix();
		SkyBox::GetInstance()->InitializeLock = true;
	}

}

void SkyBox::Update()
{
	SkyBox::GetInstance()->worldTransform_.UpdateMatrix();
}

void SkyBox::Draw(ViewProjection view)
{
	SkyBox::GetInstance()->model_->Draw(SkyBox::GetInstance()->worldTransform_,view);
}
