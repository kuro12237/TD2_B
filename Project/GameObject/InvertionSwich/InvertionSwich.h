#pragma once
#include"Model.h"
#include"GameObject/Offside/OffSideManager.h"

class InvertionSwich
{
public:
	InvertionSwich() {};
	~InvertionSwich() {};

	void Initialize(Vector3 pos);

	void Update();

	void Draw(ViewProjection view);

private:


	uint32_t Direction = Right;



};
