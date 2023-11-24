#include "OffSideManager.h"

OffsideManager* OffsideManager::GetInstance()
{
	static OffsideManager instance;
	return &instance;
}

void OffsideManager::CheckAllOffside()
{
	IOffside* offside = nullptr;
	float maxpos = OffsideManager::GetInstance()->offsides_.front()->GetPosition().x;

	for (IOffside *offsideA : OffsideManager::GetInstance()-> offsides_)
	{

		if (OffsideManager::GetInstance()->Direction_ == Left)
		{
			if (maxpos >= offsideA->GetPosition().x)
			{
				maxpos = offsideA->GetPosition().x;
				offside = offsideA;
				offside->SetPosition({ maxpos,offsideA->GetPosition().y,offsideA->GetPosition().z });

			}
		}

	     if(OffsideManager::GetInstance()->Direction_==Right)
	     {	 
	     	if ( maxpos<= offsideA->GetPosition().x)
	     	{
				maxpos = offsideA->GetPosition().x;
				offside = offsideA;
				offside->SetPosition({maxpos,offsideA->GetPosition().y,offsideA->GetPosition().z});
	     	
	     	}
	     }
	}
	OffsideManager::GetInstance()->offsidePos_ = offside->GetPosition();

}

void OffsideManager::Initialize()
{
	if (!OffsideManager::GetInstance()->InitialiseLock_)
	{
		OffsideManager::GetInstance()->leftModel_ = make_unique<Model>();
		OffsideManager::GetInstance()->leftModel_->CreateFromObj("LeftOffsidePlane");
		OffsideManager::GetInstance()->leftModel_->SetColor({ 1,1,1,1.0f });

		OffsideManager::GetInstance()->leftWorldTransform_.Initialize();
		OffsideManager::GetInstance()->leftWorldTransform_.scale = { 1,7,1 };
		OffsideManager::GetInstance()->leftWorldTransform_.UpdateMatrix();

		OffsideManager::GetInstance()->rightModel_ = make_unique<Model>();
		OffsideManager::GetInstance()->rightModel_->CreateFromObj("RightOffsidePlane");

		OffsideManager::GetInstance()->rightWorldTransform_.Initialize();
		OffsideManager::GetInstance()->rightWorldTransform_.scale = { 1,7,1 };
		OffsideManager::GetInstance()->rightWorldTransform_.translate.x = 17;
		OffsideManager::GetInstance()->rightWorldTransform_.UpdateMatrix();
		OffsideManager::GetInstance()->InitialiseLock_ = true;
	}

	OffsideManager::GetInstance()->Direction_ = Right;
}
void OffsideManager::Update()
{
	if (ImGui::TreeNode("Offside"))
	{

		ImGui::ColorPicker4("color", &OffsideManager::GetInstance()->color_.x);
		ImGui::TreePop();
	}
	if (OffsideManager::GetInstance()->Direction_ == Left)
	{
		OffsideManager::GetInstance()->leftModel_->SetColor(OffsideManager::GetInstance()->color_);
		OffsideManager::GetInstance()->leftWorldTransform_.scale = { OffsideManager::GetInstance()->offsidePos_.x,7,1 };
		OffsideManager::GetInstance()->leftWorldTransform_.UpdateMatrix();
	}
	if (OffsideManager::GetInstance()->Direction_ == Right)
	{
		OffsideManager::GetInstance()->rightModel_->SetColor(OffsideManager::GetInstance()->color_);
		OffsideManager::GetInstance()->rightWorldTransform_.scale = { 17-OffsideManager::GetInstance()->offsidePos_.x,7,1 };
		OffsideManager::GetInstance()->rightWorldTransform_.UpdateMatrix();

	}
}

void OffsideManager::Draw(ViewProjection view)
{
	if (OffsideManager::GetInstance()->Direction_ == Left)
	{
		OffsideManager::GetInstance()->leftModel_->Draw(OffsideManager::GetInstance()->leftWorldTransform_, view);
	}

	if (OffsideManager::GetInstance()->Direction_ == Right)
	{

		OffsideManager::GetInstance()->rightModel_->Draw(OffsideManager::GetInstance()->rightWorldTransform_, view);
	}
}

bool OffsideManager::ChackRightOffside()
{
	return false;
}
