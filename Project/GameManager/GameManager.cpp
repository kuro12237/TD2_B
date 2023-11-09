#include "GameManager.h"

GameManager::GameManager()
{
	Cleyera::Initialize();
	Scene_ = new GameScene();
	Scene_->Initialize();
}

GameManager::~GameManager()
{
	DebugTools::ClearCommand();
	delete Scene_;
	Cleyera::Finalize();
}

void GameManager::Run()
{
	while (WinApp::WinMsg())
	{
		Cleyera::BeginFlame();

		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.02f, 0.02f, 0.02f, 1.0f));


		ImGui::Begin("Test");

		if (ImGui::TreeNode("Scene")) {



			ImGui::TreePop();
		};
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();

		ImGui::End();


		Scene_->Update(this);

		Scene_->Back2dSpriteDraw();
		Scene_->Object3dDraw();
		Scene_->Flont2dSpriteDraw();
		//ImGui::ShowDemoWindow();

		Cleyera::EndFlame();
	}
}

void GameManager::ChangeState(IScene *newScene)
{
	DebugTools::ClearCommand();

	delete Scene_;
	Scene_ = newScene;
	Scene_->Initialize();
	return;
}
