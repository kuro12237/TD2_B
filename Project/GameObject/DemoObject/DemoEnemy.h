#pragma once
#include"Model.h"
#include"Collider.h"
#include"ColliderConfig.h"

class DemoEnemy:public Collider
{
public:
	DemoEnemy() {};
	~DemoEnemy() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override;
	void OnCollision()override;

private:
	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_{};
	uint32_t texHandle = 0;
};

