#include"MapManager.h"

MapManager* MapManager::GetInstance()
{
	static MapManager instance;
	return &instance;
}

void MapManager::Initialize()
{
	TestMap();
}

void MapManager::Update()
{
}

void MapManager::Draw()
{
}

void MapManager::TestMap()
{
	SMapData data;

	std::array<std::array<int, MapTip_MAX_X>, MapTip_MAX_Y> maptip = 
	{
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		}
	};

	data.maptip = maptip;

	MapManager::GetInstance()->mapDatas_["testData"] = make_unique<MapData>(data);
}
