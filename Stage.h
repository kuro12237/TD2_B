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
		BLOCK,//1 ��
		Barrier,//2 ��Q��
		Player1Barrier,//3 �v���C���[1����Ȃ��ƒʂ蔲���ł��Ȃ���Q��
		Player2Barrier,//4 �v���C���[2����Ȃ��ƒʂ蔲���ł��Ȃ���Q��
		Player3Barrier,//5 �v���C���[3����Ȃ��ƒʂ蔲���ł��Ȃ���Q��
		ClearBlock,//6 �N���A����
	};
};

