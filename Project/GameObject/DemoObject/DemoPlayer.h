#pragma once
#include"Input.h"
#include"Model.h"
#include"Collider.h"
#include"ColliderConfig.h"
#include"DemoPlayerBullet.h"

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


private:

	void keyControl();
	void JoyControl();

	WorldTransform worldTransform_{};
	unique_ptr<Model>model_ = nullptr;
	uint32_t texHandle_ = 0;


	list<shared_ptr<DemoPlayerBullet>>bullets_;

	
	struct PlayerVertex {//プレイヤーの四隅
		
		int RightTopX_;
		int RightBottomX_;
		int RightTopY_;
		int RightBottomY_;

		int LeftTopX_;
		int LeftBottomX_;
		int LeftTopY_;
		int LeftBottomY_;

	};
	PlayerVertex playerVertex_{};

	float PlayerRadius_=0.0f;//プレイヤーの半径

	int BlockSize_ = 32;//1ブロックあたりのサイズ



};

