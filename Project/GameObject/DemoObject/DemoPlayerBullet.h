#pragma once
#include"Model.h"
#include"Collider.h"
#include"ColliderConfig.h"
class DemoPlayerBullet:public Collider
{
public:
	DemoPlayerBullet() {};
	~DemoPlayerBullet() {};

	void Initialize(Vector3 position);

	void Update();

	void Darw(ViewProjection view);

	Vector3 GetWorldPosition();
	void OnCollision();

private:

	WorldTransform worldTransform_{};
	unique_ptr<Model>model_ = nullptr;
	uint32_t texHandle = 0;

};