#pragma once
#include"Cleyera.h"
#include"IScene.h"
#include"DebugScene.h"
#include"../DebugTools/Camera/DebugCamera.h"
#include"DemoScene.h"
class GameManager
{
public:

	GameManager();
	~GameManager();

    void Run();
    void ChangeState(IScene *newScene);

private:

	IScene* Scene_ = nullptr;

};

