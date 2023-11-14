#pragma once
#include"Pch.h"
#define MapTip_MAX_X 18
#define MapTip_MAX_Y 14

enum BLOCK
{
	AIR = 0,
	DART = 1
};

struct SMapData {
	uint32_t stageNumber;
	std::array<std::array<int, MapTip_MAX_X>, MapTip_MAX_Y> maptip;
};

class MapData
{
public:
	MapData(SMapData mapdata) { data_ = mapdata; };
	~MapData() {};

	SMapData GetMapData() { return data_; }

private:

	SMapData data_;
};
