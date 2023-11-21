#pragma once
#include"./Collider/Collider.h"
#include"./BoxCollider.h"

#include"Pch.h"
#include "VectorTransform.h"

class CollisionManager {
public:

	void CheckAllCollision();

	void BallClliderPush(Collider* collider) { colliders_.push_back(collider); }
	void BoxColliderPush(BoxCollider* collider) { BoxColliders_.push_back(collider); }

	void ClliderClear() { colliders_.clear(); BoxColliders_.clear(); }

private:
	void CheckBallCollisionPair(Collider* cA, Collider* cB);
	bool CheckBallCollosion(Vector3 v1, float vr1, Vector3 v2, float vr2);

	void CheckBoxCollisionPair(BoxCollider* cA, BoxCollider* cB);
	bool CheckBoxCollision(Vector3 v1, AABB aabb1, Vector3 v2, AABB aabb2);

	bool checkABoxRightCollision(Vector3 v1,AABB aabb1,Vector3 v2 , AABB aabb2);
	bool checkABoxLeftCoollision(Vector3 v1, AABB aabb1, Vector3 v2, AABB aabb2);

	bool checkABoxTopCollision(Vector3 v1,AABB aabb1,Vector3 v2, AABB aabb2);
	bool checkABoxDownCollision(Vector3 v1, AABB aabb1, Vector3 v2, AABB aabb2);

	Vector3 calculateBoxOverlap(Vector3& v1, AABB& aabb1, Vector3& v2, AABB& aabb2);

	list<Collider*> colliders_;
	list<BoxCollider*>BoxColliders_;
};
