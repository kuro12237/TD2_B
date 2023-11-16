#pragma once
#include"Pch.h"

struct AABB
{
	Vector3 min;
	Vector3 max;
};

class BoxCollider
{
public:
	BoxCollider() {};
	~BoxCollider() {};

	virtual void OnCollision() {};

	virtual Vector3 GetWorldPosition() = 0;

	AABB GetAABB() { return aabb_; };
	void SetAABB(AABB& aabb) { aabb_ = aabb; };

	uint32_t GetCollosionAttribute() const { return collisionAttribute_; }
	void SetCollosionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }

	uint32_t GetCollisionMask() const { return collisionMask_; }
	void SetCollisionMask(uint32_t collisionMask) { collisionMask_ = collisionMask; }


private:

	AABB aabb_ = { {-0.5f,-0.5f,-0.5f},{0.5f,0.5f,0.5f} };;

	uint32_t collisionAttribute_ = 0xffffffff;
	uint32_t collisionMask_ = 0xffffffff;

};
