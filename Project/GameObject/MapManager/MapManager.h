#pragma once
#include"Pch.h"
#include"../MapManager/Data/MapData.h"
#include"Model.h"
#include"FileLoader.h"

struct SBlock_param
{
	unique_ptr<Model> model;
	WorldTransform worldTransform;
};

class MapManager
{
public:
	
	static MapManager* GetInstance();

	static void Initialize();

	static void Update();
	
	static void Draw(ViewProjection view);

	static void SetSelectMap(uint32_t stageNumber);

	static array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> GetNowMapTip() { return MapManager::GetInstance()->NowMaptip_; }

private:

	static void CreateModels();

	static void MapTipFileLoad(const string filePath);
	static void MapTip1_10();

	uint32_t NowStageNumber_ = 0;
	uint32_t prevStageNumber_ = 0;

	//マップデータ
	map<string, unique_ptr<MapData>> mapDatas_ = {};
	//今のマップチップ
	array<array<int, MapTip_MAX_X>, MapTip_MAX_Y> NowMaptip_;
	//ModelとworldTransform
	array<array<SBlock_param,MapTip_MAX_X>,MapTip_MAX_Y> block_ = {};

	unique_ptr<Model>WorldCenterModel_ = nullptr;
	WorldTransform CenterWorldTransform_{};

	uint32_t StartTexHandle_ = 0;

#pragma region Singleton
	MapManager() = default;
	~MapManager() = default;
	MapManager(const MapManager&) = delete;
	const MapManager& operator=(const MapManager&) = delete;
#pragma endregion 
};

