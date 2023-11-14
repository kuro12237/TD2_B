#include"MapManager.h"

MapManager* MapManager::GetInstance()
{
	static MapManager instance;
	return &instance;
}

void MapManager::Initialize()
{
    CreateModels();
	TestMap();
}

void MapManager::Update()
{

	if (MapManager::GetInstance()->prevStageNumber_ != MapManager::GetInstance()->NowStageNumber_)
	{
		MapManager::GetInstance()->prevStageNumber_ = MapManager::GetInstance()->NowStageNumber_;

		for (const auto& [key, s] : MapManager::GetInstance()->mapDatas_)
		{
			key;
			if (s.get()->GetMapData().stageNumber == MapManager::GetInstance()->NowStageNumber_)
			{
				MapManager::GetInstance()->NowMaptip_ = s.get()->GetMapData().maptip;
			}
		}
	}	


	for (int y = 0; y < MapTip_MAX_Y; y++)
	{
		for (int x = 0; x < MapTip_MAX_X; x++)
		{
			MapManager::GetInstance()->block_[y][x].worldTransform.translate.x = static_cast<float>(x);
			MapManager::GetInstance()->block_[y][x].worldTransform.translate.y = static_cast<float>(MapTip_MAX_Y - y);
			MapManager::GetInstance()->block_[y][x].worldTransform.UpdateMatrix();
		}
	}
}

void MapManager::Draw(ViewProjection view)
{
	
	for (int y = 0; y < MapTip_MAX_Y; y++)
	{
		for (int x = 0; x < MapTip_MAX_X; x++)
		{
			if (MapManager::GetInstance()->NowMaptip_[y][x] == DART)
			{
				MapManager::GetInstance()->block_[y][x].model->Draw(MapManager::GetInstance()->block_[y][x].worldTransform, view);
			}
		}
	}
}

void MapManager::SetSelectMap(uint32_t stageNumber)
{
	MapManager::GetInstance()->prevStageNumber_ = MapManager::GetInstance()->NowStageNumber_;
	MapManager::GetInstance()->NowStageNumber_ = stageNumber;
}

void MapManager::CreateModels()
{	
	for (int y = 0; y < MapTip_MAX_Y; y++)
	{
		for (int x = 0; x < MapTip_MAX_X; x++)
		{
			MapManager::GetInstance()->block_[y][x].model = make_unique<Model>();
			MapManager::GetInstance()->block_[y][x].model->CreateFromObj("TestBox");
			MapManager::GetInstance()->block_[y][x].worldTransform.Initialize();
		}
	}
}

void MapManager::TestMap()
{
	SMapData data;

	std::array<std::array<int, MapTip_MAX_X>, MapTip_MAX_Y> maptip = 
	{
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

		}
	};

	SMapData data2;
	std::array<std::array<int, MapTip_MAX_X>, MapTip_MAX_Y> maptip2 =
	{
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

		}
	};

	//MapManager::GetInstance()->NowMaptip_ = maptip;

	data.stageNumber = 1;
	data.maptip = maptip;

	data2.stageNumber = 2;
	data2.maptip = maptip2;

	MapManager::GetInstance()->mapDatas_["testData"] = make_unique<MapData>(data);
	MapManager::GetInstance()->mapDatas_["testData2"] = make_unique<MapData>(data2);
}
