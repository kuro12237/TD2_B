#pragma once
#include"ViewProjection.h"
#include"WorldTransform.h"
#include"VectorTransform.h"
#include"MatrixTransform.h"

class PlayerCamera
{
public:
	PlayerCamera() {};
	~PlayerCamera() {};

	void Initialize();

	void Update(Vector3 translate);

	ViewProjection GetViewProjection() { return viewProj_; }

private:

	ViewProjection viewProj_ = {};
	Vector3 offset_{0,1,-20};


};