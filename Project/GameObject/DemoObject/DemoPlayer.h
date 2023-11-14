#pragma once
#include"Input.h"
#include"Model.h"
#include"Collider.h"
#include"ColliderConfig.h"
#include"DemoPlayerBullet.h"
struct PlayerVertex {//プレイヤーの四隅
	float RightTopX_;
	float RightBottomX_;
	float RightTopY_;
	float RightBottomY_;

	float LeftTopX_;
	float LeftBottomX_;
	float LeftTopY_;
	float LeftBottomY_;

};

class DemoPlayer:public Collider
{
public:
	DemoPlayer() {};
	~DemoPlayer() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	list<shared_ptr<DemoPlayerBullet>>GetPlayerBullets() { return bullets_; }

	Vector3 GetWorldPosition()override;
	void OnCollision()override;

	PlayerVertex GetplayerVertex_() { return playerVertex_; };

	PlayerVertex playerVertex_;
private:

	void keyControl();
	void JoyControl();

	WorldTransform worldTransform_{};
	unique_ptr<Model>model_ = nullptr;
	uint32_t texHandle_ = 0;


	list<shared_ptr<DemoPlayerBullet>>bullets_;

	

	

	float PlayerRadius_=0.0f;//プレイヤーの半径

	int BlockSize_ = 32;//1ブロックあたりのサイズ



};

