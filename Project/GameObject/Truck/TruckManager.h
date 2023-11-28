#pragma once
#include"Truck.h"

class TruckManager
{
public:
	TruckManager() {};
	~TruckManager() {};

	static TruckManager* GetInstance();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);

private:

	static void Spown();

	list<shared_ptr<Truck>>Trucks_;

	uint32_t spownTimer = 0;
	const uint32_t SpownTimerMax_ = 480;

	random_device seedGenerator;
};
