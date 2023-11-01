#pragma once
#include"Pch.h"
#include"WorldTransform.h"

struct Particle_param
{
	WorldTransform worldTransform_;
	WorldTransform uvTransform_;
	Vector4 color_{1,1,1,1};
	bool isAlive = false;
	Vector3 Velocity{};
};