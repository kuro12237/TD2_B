#include "GameManager.h"

GameManager::GameManager()
{
	Audiohandle_ = AudioManager::SoundLoadWave("Resources/sounds/GameMusic.wav");

	Cleyera::Initialize();
	Scene_ = new TitleScene();
	Scene_->Initialize();

	MapManager::Initialize();
	SceneChange::Initialize();
	SkyBox::Initialize();
	Ground::Initialize();
	TruckManager::Initialize();
	OffsideManager::Initialize();
	StageTitleName::Initialize();
}

GameManager::~GameManager()
{
	DebugTools::ClearCommand();
	delete Scene_;
	Cleyera::Finalize();
}

void GameManager::Run()
{
	this->time_++;

	if (this->time_ > 0)
	{
		this->isPlayingAudio_ = true;
	}

	if (this->isPlayingAudio_)
	{
		AudioManager::AudioPlayWave(Audiohandle_);
		this->isPlayingAudio_ = false;
	}

	if (this->time_ > 2000)
	{
		this->time_ = 0;
	}
	while (WinApp::WinMsg())
	{
		

		Cleyera::BeginFlame();

		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.02f, 0.02f, 0.02f, 1.0f));

		ImGui::Begin("Test");
		SceneChange::Update();

		Scene_->Update(this);

		

		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		
		ImGui::End();

		Scene_->Back2dSpriteDraw();
		Scene_->Object3dDraw();
		Scene_->Flont2dSpriteDraw();
		SceneChange::Draw();
		
		Cleyera::EndFlame();
	}
}

void GameManager::ChangeState(IScene *newScene)
{
	DebugTools::ClearCommand();

	delete Scene_;
	Scene_ = newScene;
	Scene_->Initialize();
	return ;
}
