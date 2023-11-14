#include"MapManager.h"

MapManager* MapManager::GetInstance()
{
	static MapManager instance;
	return &instance;
}

void MapManager::Initialize()
{
    CreateModels();

	MapTipFileLoad("Resources/MapData/stage1.csv");
	MapTipFileLoad("Resources/MapData/stage2.csv");

}

void MapManager::Update()
{
	//前のステージ番号と今のステージ番号を比べ違うときに今のステージ番号のマップをコンテナから読み込む
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

	//worldTransformとかの更新
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



void MapManager::MapTipFileLoad(const string filePath)
{
	stringstream file;
	file = FileLoader::CSVLoadFile(filePath);
	
	string line;
	uint32_t stageNumber = 0;
	array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> Maptip{};
	int y = -1;

	while(getline(file, line))
	{
		istringstream line_stream(line);
		string word;
		getline(line_stream, word, ',');
		
		if (word.find("//") == 0)
		{
			continue;
		}

		if (word.find("MapNumber") == 0)
		{
			getline(line_stream, word, ',');
			stageNumber = (uint32_t)std::atof(word.c_str());
		}
	
		if (word.find("MapTip") == 0)
		{
			for (int x = 0; x < 18; x++)
			{
				getline(line_stream, word, ',');
				Maptip[y][x] = (int)atoi(word.c_str());
			}
		}
		y++;
	}

	SMapData data;
	data.maptip = Maptip;
	data.stageNumber = stageNumber;
	MapManager::GetInstance()->mapDatas_[filePath] = make_unique<MapData>(data);
}
