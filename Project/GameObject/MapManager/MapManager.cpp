#include"MapManager.h"

MapManager* MapManager::GetInstance()
{
	static MapManager instance;
	return &instance;
}

void MapManager::Initialize()
{
    CreateModels();

	MapTip1_10();
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
			MapManager::GetInstance()->block_[y][x].worldTransform.translate.y = static_cast<float>(MapTip_MAX_Y - y-0.5f);
			MapManager::GetInstance()->block_[y][x].worldTransform.UpdateMatrix();
			

		}
	}
	MapManager::GetInstance()->CenterWorldTransform_.UpdateMatrix();
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
	MapManager::GetInstance()->WorldCenterModel_->Draw(MapManager::GetInstance()->CenterWorldTransform_, view);
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
	MapManager::GetInstance()->WorldCenterModel_ = make_unique<Model>();
	MapManager::GetInstance()->WorldCenterModel_->Initialize(new ModelSphereState);
	MapManager::GetInstance()->CenterWorldTransform_.Initialize();
	MapManager::GetInstance()->CenterWorldTransform_.scale = { 1,1,1 };
	MapManager::GetInstance()->WorldCenterModel_->SetColor({ 1,0,0,1 });
	MapManager::GetInstance()->CenterWorldTransform_.UpdateMatrix();

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
			y++;
			for (int x = 0; x < 18; x++)
			{
				getline(line_stream, word, ',');
				Maptip[y][x] = (int)atoi(word.c_str());
			}
		}
	
	}

	int testmap[MapTip_MAX_Y][MapTip_MAX_X]{};
	
	for (int i = 0; i < MapTip_MAX_Y; i++)
	{
		for (int j = 0; j < MapTip_MAX_X; j++)
		{

			testmap[i][j] = Maptip[i][j];
		}

	}
	testmap;

	SMapData data;
	data.maptip = Maptip;
	data.stageNumber = stageNumber;
	MapManager::GetInstance()->mapDatas_[filePath] = make_unique<MapData>(data);
}

void MapManager::MapTip1_10()
{
	MapTipFileLoad("Resources/MapData/stage1.csv");
	MapTipFileLoad("Resources/MapData/stage2.csv");
	MapTipFileLoad("Resources/MapData/stage3.csv");
	MapTipFileLoad("Resources/MapData/stage4.csv");
	MapTipFileLoad("Resources/MapData/stage5.csv");
}
