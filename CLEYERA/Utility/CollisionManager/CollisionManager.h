#pragma once
#include"./Collider/Collider.h"
#include"Pch.h"
#include "VectorTransform.h"

class CollisionManager {
public:

	void CheckAllCollision();

	void ClliderPush(Collider* collider) { colliders_.push_back(collider); }
	void ClliderClear() { colliders_.clear(); }

private:
	void CheckCollisionPair(Collider* cA, Collider* cB);
	bool CheckBallCollosion(Vector3 v1, float vr1, Vector3 v2, float vr2);

	std::list<Collider*> colliders_;
};
