#include"MapManager.h"

MapManager* MapManager::GetInstance()
{
	static MapManager instance;
	return &instance;
}

void MapManager::Initialize()
{
    CreateModels();

	MapManager::GetInstance()->StartTexHandle_ = TextureManager::LoadTexture("Resources/BlockTex/StartTex.png");
	MapManager::GetInstance()->GoalTexHandle_ = TextureManager::LoadTexture("Resources/BlockTex/GoalTex.png");
	MapManager::GetInstance()->BaggageTexHandle_ = TextureManager::LoadTexture("Resources/BlockTex/BaggageSpownTex.png");
	MapManager::GetInstance()->BlockDartTex_ = TextureManager::LoadTexture("Resources/BlockTex/woodTex.png");
	MapManager::GetInstance()->LadderTex_ = TextureManager::LoadTexture("Resources/BlockTex/LadderTex.png");
	MapManager::GetInstance()->InvertionSwich = TextureManager::LoadTexture("Resources/BlockTex/InvertionSwichSpownTex.png");
	MapTip1_10();
	MapTipLoad11_20();
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
				MapManager::GetInstance()->block_[y][x].model->SetTexHandle(MapManager::GetInstance()->BlockDartTex_);
				MapManager::GetInstance()->block_[y][x].model->Draw(MapManager::GetInstance()->block_[y][x].worldTransform, view);				
			}
			if (MapManager::GetInstance()->NowMaptip_[y][x] == LADER)
			{
				MapManager::GetInstance()->block_[y][x].model->SetTexHandle(MapManager::GetInstance()->LadderTex_);
				MapManager::GetInstance()->block_[y][x].model->Draw(MapManager::GetInstance()->block_[y][x].worldTransform, view);
			}
			if (MapManager::GetInstance()->NowMaptip_[y][x] == START)
			{
				MapManager::GetInstance()->block_[y][x].model->SetTexHandle(MapManager::GetInstance()->StartTexHandle_);
				MapManager::GetInstance()->block_[y][x].model->Draw(MapManager::GetInstance()->block_[y][x].worldTransform, view);
			}
			
			if (MapManager::GetInstance()->NowMaptip_[y][x] == GOAL)
			{
				MapManager::GetInstance()->block_[y][x].model->SetTexHandle(MapManager::GetInstance()->GoalTexHandle_);
				MapManager::GetInstance()->block_[y][x].model->Draw(MapManager::GetInstance()->block_[y][x].worldTransform, view);
			}
			
			if (MapManager::GetInstance()->NowMaptip_[y][x] == BAGGAGESPOWN)
			{
				MapManager::GetInstance()->block_[y][x].model->SetTexHandle(MapManager::GetInstance()->BaggageTexHandle_);
				MapManager::GetInstance()->block_[y][x].model->Draw(MapManager::GetInstance()->block_[y][x].worldTransform, view);
			}
			if (MapManager::GetInstance()->NowMaptip_[y][x] == INVERSIONSWICH)
			{
				MapManager::GetInstance()->block_[y][x].model->SetTexHandle(MapManager::GetInstance()->InvertionSwich);
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
	MapManager::GetInstance()->WorldCenterModel_ = make_unique<Model>();
	MapManager::GetInstance()->WorldCenterModel_->Initialize(new ModelSphereState);
	MapManager::GetInstance()->CenterWorldTransform_.Initialize();
	MapManager::GetInstance()->CenterWorldTransform_.scale = { 1,1,1 };
	MapManager::GetInstance()->CenterWorldTransform_.translate = { 0,0,0 };
	//MapManager::GetInstance()->WorldCenterModel_->SetColor({ 1,0,0,1 });
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
			for (int x = 0; x < MapTip_MAX_X; x++)
			{
				getline(line_stream, word, ',');
				Maptip[y][x] = (int)atoi(word.c_str());
			}
		}
	
	}
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
	MapTipFileLoad("Resources/MapData/stage6.csv");
	MapTipFileLoad("Resources/MapData/stage7.csv");
	MapTipFileLoad("Resources/MapData/stage8.csv");
	MapTipFileLoad("Resources/MapData/stage9.csv");
	MapTipFileLoad("Resources/MapData/stage10.csv");
}

void MapManager::MapTipLoad11_20()
{
	MapTipFileLoad("Resources/MapData/stage11.csv");
	MapTipFileLoad("Resources/MapData/stage12.csv");
	MapTipFileLoad("Resources/MapData/stage13.csv");
	MapTipFileLoad("Resources/MapData/stage14.csv");
	MapTipFileLoad("Resources/MapData/stage15.csv");
	MapTipFileLoad("Resources/MapData/stage16.csv");
	MapTipFileLoad("Resources/MapData/stage17.csv");
	MapTipFileLoad("Resources/MapData/stage18.csv");
	MapTipFileLoad("Resources/MapData/stage19.csv");
	MapTipFileLoad("Resources/MapData/stage20.csv");
}
