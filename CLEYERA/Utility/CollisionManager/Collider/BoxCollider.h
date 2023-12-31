#pragma once
#include"Pch.h"

struct AABB
{
	Vector3 min;
	Vector3 max;
};

enum Direction
{
	Top,
	Down,
	Left,
	Right
};

class BoxCollider
{
public:
	BoxCollider() {};
	~BoxCollider() {};

	virtual void OnCollision(Vector3 overlap,Vector3 position,Vector3 velocity,uint32_t id) = 0;

	virtual void OnRightCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id) = 0;
	virtual void OnLeftCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id) = 0;

	virtual void OnTopCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id) = 0;

	virtual void OnDownCollision(Vector3 overlap, Vector3 position, Vector3 velocity, uint32_t id) = 0;

	virtual Vector3 GetWorldPosition() = 0;

	AABB GetAABB() { return aabb_; };
	void SetAABB(AABB& aabb) { aabb_ = aabb; };

	uint32_t GetCollosionAttribute() const { return collisionAttribute_; }
	void SetCollosionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }

	uint32_t GetCollisionMask() const { return collisionMask_; }
	void SetCollisionMask(uint32_t collisionMask) { collisionMask_ = collisionMask; }

	void SetBoxVelocity(Vector3 v) { velocity_ = v; }
	Vector3 GetBoxVelocity() { return velocity_; }

	void SetObjectId(uint32_t id) { id_ = id; }
	uint32_t GetObjectId() { return id_; }

private:

	AABB aabb_ = { {-0.5f,-0.5f,-0.5f},{0.5f,0.5f,0.5f} };;

	uint32_t collisionAttribute_ = 0xffffffff;
	uint32_t collisionMask_ = 0xffffffff;
	Vector3 velocity_ = {};

	uint32_t id_ = 0xffffffff;
};
