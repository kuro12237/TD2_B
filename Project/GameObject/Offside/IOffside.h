#pragma once
#include"WorldTransform.h"

class IOffside
{
public:
	IOffside() {};
	~IOffside() {};

	void SetPosition(Vector3 pos) { pos_ = pos; }
	
	Vector3 GetPosition() { return pos_; }

private:

	Vector3 pos_ = {};


};
