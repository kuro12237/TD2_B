#include"CollisionManager.h"


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

		Vector3 oAoverlap{}, oBoverlap{};

		//めり込み計算
		oAoverlap = calculateBoxOverlap(cApos, aabbA,cBpos,aabbB);
		oBoverlap = calculateBoxOverlap(cBpos, aabbB, cApos, aabbA);


		cA->OnCollision(oBoverlap, cB->GetWorldPosition(), cB->GetBoxVelocity());
		cB->OnCollision(oAoverlap, cA->GetWorldPosition(), cA->GetBoxVelocity());

		//右
	    //Aの右に当たった時Bの左の関数を使う
		if (checkABoxRightCollision(cA->GetWorldPosition(), aabbA, cB->GetWorldPosition(), aabbB))
		{
			cA->OnLeftCollision(oBoverlap, cB->GetWorldPosition(), cB->GetBoxVelocity());
			cB->OnRightCollision(oAoverlap, cA->GetWorldPosition(), cA->GetBoxVelocity());
		}

		//左
		else if (checkABoxLeftCoollision(cA->GetWorldPosition(),aabbA,cB->GetWorldPosition(), aabbB))
		{
			cA->OnRightCollision(oBoverlap, cB->GetWorldPosition(), cB->GetBoxVelocity());
			cB->OnLeftCollision(oAoverlap, cA->GetWorldPosition(), cA->GetBoxVelocity());
			//return;
		}
	
		//上
		if (checkABoxTopCollision(cA->GetWorldPosition(), aabbA, cB->GetWorldPosition(), aabbB))
		{
			cA->OnTopCollision(oBoverlap, cB->GetWorldPosition(), cB->GetBoxVelocity());
			cB->OnTopCollision(oAoverlap, cA->GetWorldPosition(), cA->GetBoxVelocity());
		}
		else if(checkABoxDownCollision(cA->GetWorldPosition(),aabbA,cB->GetWorldPosition(),aabbB))
		{
			cA->OnDownCollision(oBoverlap, cB->GetWorldPosition(), cB->GetBoxVelocity());
			cB->OnDownCollision(oAoverlap, cA->GetWorldPosition(), cA->GetBoxVelocity());
		}
		


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

bool CollisionManager::checkABoxRightCollision(Vector3 v1, AABB aabb1, Vector3 v2, AABB aabb2)
{
	v1, v2;
	if (v1.x + aabb1.max.x-0.2f > v2.x + aabb2.min.x && v1.y > v2.y - 0.1f&& v1.y < v2.y + 0.1f)
	{
		return true;
	}
	return false;
}

bool CollisionManager::checkABoxLeftCoollision(Vector3 v1,AABB aabb1, Vector3 v2,AABB aabb2)
{

	v1, v2;
	if (v1.x + aabb1.min.x +0.2f< v2.x + aabb2.max.x && v1.y > v2.y - 0.1f && v1.y < v2.y + 0.1f)
	{
		return true;
	}
	return false;
}

bool CollisionManager::checkABoxTopCollision(Vector3 v1,AABB aabb1, Vector3 v2,AABB aabb2)
{
	v1, v2;
	aabb1, aabb2;
	if (v1.y + aabb1.min.y  < v2.y + aabb2.max.y && v1.x > v2.x - 0.9f && v1.x < v2.x + 0.9f)
	{
		return true;
	}
	return false;
}

bool CollisionManager::checkABoxDownCollision(Vector3 v1, AABB aabb1, Vector3 v2, AABB aabb2)
{
	v1, v2;
	aabb1, aabb2;
	if (v1.y + aabb1.max.y  < v2.y + aabb2.min.y && v1.x > v2.x - 0.9f && v1.x < v2.x + 0.9f)
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
