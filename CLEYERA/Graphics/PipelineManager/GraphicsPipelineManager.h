#pragma once
#include"LogManager.h"
#include"DirectXCommon.h"
#include"ShaderManager.h"

struct SPSOProperty
{
	ComPtr<ID3D12PipelineState> GraphicsPipelineState = nullptr;
	ComPtr<ID3D12RootSignature> rootSignature = nullptr;
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;

};

struct  SBlendPSO
{
	SPSOProperty none;
	SPSOProperty Add;
	SPSOProperty Subtruct;
	SPSOProperty Multiply;
	SPSOProperty Screen;

};

struct SPSO
{
	SPSOProperty shape;
	SPSOProperty Line;
	SBlendPSO Sprite2d;
	SBlendPSO Sprite3d;
	SBlendPSO Particle3d;
	SPSOProperty Herf_Lambert;
};

enum  BlendMode
{
	BlendNone,
	BlendAdd,
	BlendSubtruct,
	BlendMultiply,
	BlendScreen,
};

class GraphicsPipelineManager
{
public:

	static GraphicsPipelineManager* GetInstance();

	static void Initialize();
    SPSO GetPso() { return pso; }

private:

	static void CreateRootSignature(
		ComPtr<ID3D12Device> device,
		D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature,
		SPSOProperty& result
	);

	/// <summary>
	/// InputElement�̐ݒ�
	/// </summary>
	/// <param name="inputElementDescs"></param>
	/// <param name="SemanticName"></param>
	/// <param name="SemanticIndex"></param>
	/// <param name="Format"></param>
	/// <param name="AlignedByteOffset"></param>
	static void SettingInputElementDesc(
		D3D12_INPUT_ELEMENT_DESC &inputElementDescs,
		LPCSTR SemanticName,
		UINT SemanticIndex,
		DXGI_FORMAT Format,
		UINT AlignedByteOffset
		);

	/// <summary>
	/// �u�����h���[�h�̐ݒ�
	/// </summary>
	/// <param name="blenddesc"></param>
	/// <param name="mode"></param>
	static void SettingBlendState(
		D3D12_RENDER_TARGET_BLEND_DESC& blenddesc,
		BlendMode mode);

	/// <summary>
	/// ���X�^���C�U�[�̐ݒ�
	/// </summary>
	/// <param name="rasterizerDesc"></param>
	/// <param name="CullMode : �ǂ̌����ɕ\�����邩"></param>
	/// <param name="FillMode : �h��Ԃ���"></param>
	static void SettingRasterizer(
		D3D12_RASTERIZER_DESC& rasterizerDesc,
		D3D12_CULL_MODE CullMode,
		D3D12_FILL_MODE FillMode
	);

	/// <summary>
	/// �[�x�̐ݒ�
	/// </summary>
	/// <param name="despthStencilDesc"></param>
	/// <param name="EnableFlag"></param>
	/// <param name="writeMask"></param>
	/// <param name="Func"></param>
	static void SettingDepth(
		D3D12_DEPTH_STENCIL_DESC &despthStencilDesc,
		bool EnableFlag,
		D3D12_DEPTH_WRITE_MASK writeMask,
		D3D12_COMPARISON_FUNC Func
	);


	static void CreatePSO(SPSO &pso);
	static void Create2dSpritePSOs(SPSO &pso);
	static void Create3dSpritePSOs(SPSO& pso);
	static void Create3dParticlePSOs(SPSO& pso);

	static SPSOProperty CreateShape(ComPtr<ID3D12Device>device,Commands command,SShaderMode shader);
	static SPSOProperty CreateLine(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite3dNone(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateSprite2dNone(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dAdd(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dSubtract(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dMultiply(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dScreen(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateHerf_Lambert(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateParticle3dNone(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateParticle3dAdd(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	SPSO pso = {};

};

