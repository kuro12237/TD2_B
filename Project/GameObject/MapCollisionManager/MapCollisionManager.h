#pragma once
#include"Pch.h"
#include"MapCollider.h"
#include"../MapManager/MapManager.h"

struct  SCebeVertex
{
	float top, down, right, left;
};

class MapCollisionManager
{
public:
	MapCollisionManager() {};
	~MapCollisionManager() {};


	void ClearList();

	void AddCollider(MapCollider* collider) { colliders_.push_back(collider); }

	void ChackAllCollision();

private:

	void Collision(MapCollider* ob1);

	bool CheckLehtRight(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map,SCebeVertex c,Vector2 velosity);
	bool CheckIsRightMove(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map, SCebeVertex c);
	bool CheckIsLeftMove(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map, SCebeVertex c);

	bool CheckTopDown(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map, SCebeVertex c, Vector2 velosity);
	bool CheckIsTopMove(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map, SCebeVertex c);
	bool CheckIsDownMove(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map, SCebeVertex c);


	list<MapCollider*>colliders_{};
};

