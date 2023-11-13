#pragma once
#include"Pch.h"
#include"../MapManager/Data/MapData.h"

class MapManager
{
public:
	
	static MapManager* GetInstance();

	static void Initialize();

	static void Update();
	
	static void Draw();

private:

	static void TestMap();

	map<string, unique_ptr<MapData>> mapDatas_ = {};


#pragma region Singleton
	MapManager() = default;
	~MapManager() = default;
	MapManager(const MapManager&) = delete;
	const MapManager& operator=(const MapManager&) = delete;
#pragma endregion 
};

