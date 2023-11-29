#pragma once
#include"Cleyera.h"
#include"IScene.h"
#include"DebugScene.h"
#include"../DebugTools/Camera/DebugCamera.h"
#include"GameScene.h"
#include"Title/TitleScene.h"

#include"GameObject/SkyBox/SkyBox.h"
#include"GameObject/Ground/Ground.h"
#include"GameObject/Truck/TruckManager.h"

class GameManager
{
public:

	GameManager();
	~GameManager();

    void Run();
    void ChangeState(IScene *newScene);



private:

	IScene* Scene_ = nullptr;
	uint32_t Audiohandle_ = 0;
	bool isPlayerAudio = false;
	int time = 600;

};

