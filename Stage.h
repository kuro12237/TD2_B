#pragma once
#include"Input.h"
#include"Model.h"
#include"Collider.h"
#include"ColliderConfig.h"
#include"GameObject/DemoObject/DemoPlayer.h"
#include"Vector2.h"
class Stage:public Collider
{
public:
	void Initilize();
	void Updata();
	void Draw(ViewProjection view);
	int Map[8][8];
private:
	
	int MapCountX;
	int MapCountY;
	float Speed;

	WorldTransform worldTransform_{};
	unique_ptr<Model>model_ = nullptr;
	uint32_t texHandle_ = 0;

	DemoPlayer* Player_ = nullptr;

	//list<shared_ptr<DemoPlayer>>Player_;

	enum Mapinfo
	{
		NONE,//0  
		BLOCK,//1 壁
		Barrier,//2 障害物
		Player1Barrier,//3 プレイヤー1じゃないと通り抜けできない障害物
		Player2Barrier,//4 プレイヤー2じゃないと通り抜けできない障害物
		Player3Barrier,//5 プレイヤー3じゃないと通り抜けできない障害物
		ClearBlock,//6 クリア判定
	};
};

