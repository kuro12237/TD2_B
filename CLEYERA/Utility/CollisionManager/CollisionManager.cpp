﻿#include"CollisionManager.h"


void CollisionManager::CheckAllCollision()
{
	//Ball
	std::list<Collider*>::iterator itrA = colliders_.begin();

	for (; itrA != colliders_.end(); ++itrA) {

		Collider* colliderA = *itrA;

		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;
			
			CheckBallCollisionPair(colliderA, colliderB);
		}
	}

	//Box
	list<BoxCollider*>::iterator itrBoxA = BoxColliders_.begin();

	for (; itrBoxA != BoxColliders_.end(); ++itrBoxA) {

		BoxCollider* colliderA = *itrBoxA;

		list<BoxCollider*>::iterator itrBoxB = itrBoxA;
		itrBoxB++;
		for (; itrBoxB != BoxColliders_.end(); ++itrBoxB) {
			BoxCollider* colliderB = *itrBoxB;
		
			CheckBoxCollisionPair(colliderA, colliderB);
		}
	}
}

void CollisionManager::CheckBallCollisionPair(Collider* cA, Collider* cB) {

	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0) {
		return;
	}

	Vector3 cApos = cA->GetWorldPosition();
	Vector3 cBpos = cB->GetWorldPosition();

	float cAradious = cA->GetRadious();
	float cBradious = cB->GetRadious();

	if (CheckBallCollosion(cApos, cAradious, cBpos, cBradious)) {
		cA->OnCollision();
		cB->OnCollision();
	}
}


bool CollisionManager::CheckBallCollosion(Vector3 v1, float vr1, Vector3 v2, float vr2) {
	float x = (v2.x - v1.x);
	float y = (v2.y - v1.y);
	float z = (v2.z - v1.z);

	float resultPos = (x * x) + (y * y) + (z * z);

	float resultRadious = vr1 + vr2;

	bool Flag = false;

	if (resultPos <= (resultRadious * resultRadious)) {
		Flag = true;
	}

	return Flag;
}

void CollisionManager::CheckBoxCollisionPair(BoxCollider* cA, BoxCollider* cB)
{
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0) {
		return;
	}

	Vector3 cApos = cA->GetWorldPosition();
	Vector3 cBpos = cB->GetWorldPosition();

	AABB aabbA = cA->GetAABB();
	//コライダーBのAABBを取得
	AABB aabbB = cB->GetAABB();

	if (CheckBoxCollision(cApos, aabbA, cBpos, aabbB)) {

		Vector3 oA{}, oB{};

		oA = calculateBoxOverlap(cApos, aabbA,cBpos,aabbB);
		oB = calculateBoxOverlap(cBpos, aabbB, cApos, aabbA);

		cA->OnCollision(oB,cB->GetWorldPosition(), cB->GetBoxVelocity());
		cB->OnCollision(oA,cA->GetWorldPosition(), cA->GetBoxVelocity());
	}

}

bool CollisionManager::CheckBoxCollision(Vector3 v1, AABB aabb1, Vector3 v2, AABB aabb2)
{
	if (v1.x + aabb1.min.x <= v2.x + aabb2.max.x && v1.x + aabb1.max.x >= v2.x + aabb2.min.x &&
		v1.y + aabb1.min.y <= v2.y + aabb2.max.y && v1.y + aabb1.max.y >= v2.y + aabb2.min.y &&
		v1.z + aabb1.min.z <= v2.z + aabb2.max.z && v1.z + aabb1.max.z >= v2.z + aabb2.min.z) 
	{
		return true;
	}
	return false;
}

bool CollisionManager::chackBoxLeftCollision(Vector3 v1, AABB aabb1, Vector3 v2, AABB aabb2)
{
	if (aabb1.max.x >= aabb2.min.x && aabb1.min.x <= aabb2.max.x && // x軸方向のチェック
		aabb1.max.y >= aabb2.min.y && aabb1.min.y <= aabb2.max.y && // y軸方向のチェック
		aabb1.max.z >= aabb2.min.z && aabb1.min.z <= aabb2.max.z)
	{
		return true;
	}

	return false;
}

Vector3 CollisionManager::calculateBoxOverlap(Vector3& v1, AABB& aabb1, Vector3& v2, AABB& aabb2)
{
	Vector3 overlap;
    overlap.x = min<float>(v1.x + aabb1.max.x - v2.x - aabb2.min.x, v2.x + aabb2.max.x - v1.x - aabb1.min.x);
    overlap.y = min<float>(v1.y + aabb1.max.y - v2.y - aabb2.min.y, v2.y + aabb2.max.y - v1.y - aabb1.min.y);
    overlap.z = min<float>(v1.z + aabb1.max.z - v2.z - aabb2.min.z, v2.z + aabb2.max.z - v1.z - aabb1.min.z);
   	overlap.x = max<float>(overlap.x, 0.0);
    overlap.y = max<float>(overlap.y, 0.0);
    overlap.z = max<float>(overlap.z, 0.0);
    return overlap;
}
