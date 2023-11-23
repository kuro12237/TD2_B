#include "TruckManager.h"

TruckManager* TruckManager::GetInstance()
{
	static TruckManager instance;
	return &instance;
}

void TruckManager::Initialize()
{
	shared_ptr<Truck>truck = make_shared<Truck>();
	truck->Initialize();
	TruckManager::GetInstance()->Trucks_.push_back(truck);
}

void TruckManager::Update()
{
	TruckManager::GetInstance()->Trucks_.remove_if([](std::shared_ptr<Truck>& e) {
		if (!e->GetAlive())
		{
			e.reset();
			return true;
		}
		return false;
	});

	Spown();

	for (shared_ptr<Truck>truck : TruckManager::GetInstance()->Trucks_)
	{
		truck->Update();
	}
}

void TruckManager::Draw(ViewProjection view)
{
	for (shared_ptr<Truck>truck : TruckManager::GetInstance()->Trucks_)
	{
		truck->Draw(view);
	}
}

void TruckManager::Spown()
{
	TruckManager::GetInstance()->spownTimer++;

	if (TruckManager::GetInstance()->spownTimer > TruckManager::GetInstance()->SpownTimerMax_)
	{
		shared_ptr<Truck>truck = make_shared<Truck>();
		truck->Initialize();
		TruckManager::GetInstance()->Trucks_.push_back(truck);

		TruckManager::GetInstance()->spownTimer = 0;
	}

}
