#include"ImGuiManager.h"



ImGuiManager::ImGuiManager()
{
}

void ImGuiManager::Initialize()
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(WinApp::GetInstance()->GetHwnd());
	ImGui_ImplDX12_Init(
		DirectXCommon::GetInstance()->GetDevice().Get(),
		DirectXCommon::GetInstance()->GetswapChain().swapChainDesc.BufferCount,
		DirectXCommon::GetInstance()->GetRtv().rtvDesc.Format,
		DirectXCommon::GetInstance()->GetSrvHeap().Get(),
		DirectXCommon::GetInstance()->GetSrvHeap()->GetCPUDescriptorHandleForHeapStart(),
		DirectXCommon::GetInstance()->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart()

	);
}

void ImGuiManager::BeginFlame()
{

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ID3D12DescriptorHeap* descripterHeap[] = { DirectXCommon::GetInstance()->GetSrvHeap().Get()};
	DirectXCommon::GetInstance()->GetCommands().m_pList->SetDescriptorHeaps(1, descripterHeap);

}

void ImGuiManager::EndFlame()
{

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), DirectXCommon::GetInstance()->GetCommands().m_pList.Get());

}

void ImGuiManager::Finalize()
{
	ImGui_ImplDX12_Shutdown();
}

void ImGuiManager::UpdateUI()
{
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.02f, 0.02f, 0.02f, 1.0f));


	ImGui::Begin("Test");

	if (ImGui::TreeNode("Scene")) {



		ImGui::TreePop();
	};
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::End();
}


