#include "MapCollisionManager.h"

void MapCollisionManager::ClearList()
{
	colliders_.clear();
}

void MapCollisionManager::ChackAllCollision()
{
	std::list<MapCollider*>::iterator itrA = colliders_.begin();

	for (; itrA != colliders_.end(); ++itrA) {

		MapCollider* colliderA = *itrA;
		Collision(colliderA);
	}

}

void MapCollisionManager::Collision(MapCollider* ob1)
{
	const float gap =  0.1f;

	SCebeVertex CubeA{};
	CubeA.top = ob1->GetWorldPosition().y -ob1->GetRadious() + gap;
	CubeA.down = ob1->GetWorldPosition().y  +ob1->GetRadious() - gap-0.1f;
	CubeA.right = ob1->GetWorldPosition().x +(ob1->GetRadious() + ob1->GetRadious() + gap-0.1f);
	CubeA.left = ob1->GetWorldPosition().x -(ob1->GetRadious() - ob1->GetRadious() - gap);

	Vector2 velocity = ob1->GetVelocity();

	array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map = {};
	
	//マップチップ反転Y
	for (int i = 0; i < MapTip_MAX_Y; i++)
	{
		for (int j = 0; j < MapTip_MAX_X; j++)
		{
			map[MapTip_MAX_Y - i - 1][j] = MapManager::GetNowMapTip()[i][j];
		}
	}

	//左右移動チェック
	if (CheckLehtRight(map, CubeA, velocity))
	{
		//uint32_t nowPos = CheckNowPosMapData(map, ob1->GetWorldPosition());
		//nowPos;
		//右に動いているときのチェック
		if (velocity.x > 0)
		{
			//uint32_t p = map[(int)(ob1->GetWorldPosition().y)][(int)(ob1->GetWorldPosition().x + 1.0f+0.1f)];
			//p; 
			if (!CheckIsRightMove(map, CubeA))
			{
				ob1->RightCollision(0);
			}
		}
		//左に動いているときのチェック
		if (velocity.x < 0)
		{
			//uint32_t p = map[(int)(ob1->GetWorldPosition().y)][(int)(ob1->GetWorldPosition().x - 1.0f-0.2f)];
			//p;
			if (!CheckIsLeftMove(map, CubeA))
			{
				ob1->LeftCollision(0);
			}
		}
	}

	//上下移動チェック
	if (CheckTopDown(map, CubeA, velocity))
	{
		//uint32_t nowPos = CheckNowPosMapData(map, ob1->GetWorldPosition());
		//nowPos;
		//上
		if (velocity.y > 0)
		{
			
			if (!CheckIsTopMove(map, CubeA))
			{
				//uint32_t p =map[(int)(CubeA.top)][(int)(CubeA.right) + 1];
				ob1->TopCollision(0);
			}
		}
		//下
		if (velocity.y < 0)
		{
		
			if (!CheckIsDownMove(map, CubeA))
			{
				ob1->DownCollision(0);
			}
		}
	}

}

bool MapCollisionManager::CheckLehtRight(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map,SCebeVertex c, Vector2 velocity)
{
	if(map[(int)(c.top)][(int)(c.left + velocity.x)] != 0 || map[(int)(c.top)][(int)(c.right+ velocity.x)] != 0 ||
	   map[(int)(c.down)][(int)(c.left + velocity.x)] != 0 || map[(int)(c.down)][(int)(c.right+velocity.x)] != 0 
	
		)
	{
		return true;
	}
	return false;
}

bool MapCollisionManager::CheckIsRightMove(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map, SCebeVertex c)
{
	while (map[(int)(c.top)][(int)(c.left) + 1] == 0 && map[(int)(c.top)][(int)(c.right) + 1] == 0 &&
		map[(int)c.down][(int)(c.left) + 1] == 0 && map[(int)c.down][(int)(c.right) + 1] == 0
		)
	{
		return true;
	}
	return false;
}

bool MapCollisionManager::CheckIsLeftMove(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map, SCebeVertex c)
{
	while (map[(int)(c.top)][(int)(c.left)-1] == 0 && map[(int)(c.top)][(int)(c.right)-1] == 0 && 
		map[(int)c.down][(int)(c.left)-1] == 0 && map[(int)c.down][(int)(c.right)-1] == 0
		)
	{
		return true;
	}
	return false;
}

bool MapCollisionManager::CheckTopDown(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map, SCebeVertex c, Vector2 velocity)
{
	if (map[(int)(c.top + velocity.y)][(int)(c.left )] != 0 || map[(int)(c.top + velocity.y)][(int)(c.right)] != 0 ||
		map[(int)(c.down + velocity.y)][(int)(c.left)] != 0 || map[(int)(c.down + velocity.y)][(int)(c.right)] != 0
		)
	{
		return true;
	}
	return false;
}

bool MapCollisionManager::CheckIsTopMove(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map, SCebeVertex c)
{
	while (map[(int)(c.top + 1)][(int)(c.left)] == 0 && map[(int)(c.top + 1)][(int)(c.right)] == 0 &&
		map[(int)(c.down + 1)][(int)(c.left)] == 0 && map[(int)(c.down + 1)][(int)(c.right)] == 0
	)
	{
		return true;
	}
	return false;
}

bool MapCollisionManager::CheckIsDownMove(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map, SCebeVertex c)
{
	while (map[(int)(c.top - 1)][(int)(c.left)] == 0 && map[(int)(c.top - 1)][(int)(c.right)] == 0 &&
		map[(int)(c.down - 1)][(int)(c.left)] == 0 && map[(int)(c.down - 1)][(int)(c.right)] == 0
		)
	{
		return true;
	}
	return false;
}

SCebeVertex MapCollisionManager::CheckNowPosMapData(array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> map, SCebeVertex pos)
{
	SCebeVertex result{};
	map;
	pos;
	return result;
}
