#pragma once
#include"WorldTransform.h"

class IOffside
{
public:
	IOffside() {};
	~IOffside() {};

	void SetPosition(Vector3 pos) { pos_ = pos; }
	
	Vector3 GetPosition() { return pos_; }

	Vector3 GetVelocity() { return velocity_;}
	void SetVec3Velocity(Vector3 v) { velocity_ = v; }

private:

	Vector3 pos_ = {};
	Vector3 velocity_ = {};

};
