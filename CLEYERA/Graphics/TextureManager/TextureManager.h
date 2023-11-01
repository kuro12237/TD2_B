#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"WinApp.h"
#include"CreateResource.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"Graphics/TextureManager/TexDataResource.h"

class TextureManager
{
public:
	
	static TextureManager* GetInstance();

	static void Initialize();
	static void Finalize();

	static uint32_t LoadTexture(const string& filePath);
	static void UnLoadTexture(const string& filePath);
	static void AllUnLoadTexture();

private:

	static ComPtr<ID3D12Resource> CreateTexResource(const DirectX::TexMetadata& metadata);

	static DirectX::ScratchImage CreateMipImage(const std::string& filePath);

	static D3D12_RESOURCE_DESC SettingResource(const DirectX::TexMetadata& metadata);

	static D3D12_HEAP_PROPERTIES SettingHeap();

	static void UploadMipImage(const DirectX::TexMetadata& metadata, DirectX::ScratchImage &mipImages, TexData texData);

	static D3D12_SHADER_RESOURCE_VIEW_DESC SrcDescSetting(const DirectX::TexMetadata& metadata);

	static void AddDescripter(uint32_t index, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc,ID3D12Resource *resource);

	static bool CheckTexDatas(string filePath);

	map<string, unique_ptr<TexDataResource>>texDatas_;

#pragma region 
	//Singleton
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	const TextureManager& operator=(const TextureManager&) = delete;
#pragma endregion 
};


