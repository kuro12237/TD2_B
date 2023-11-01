#include"ModelCubeState.h"


void ModelCubeState::Initialize(Model* state)
{
	int v = VertexNum;
	resource_.Vertex = CreateResources::CreateBufferResource(sizeof(VertexData) * v);
	resource_.Material = CreateResources::CreateBufferResource(sizeof(Material));
	resource_.wvpResource = CreateResources::CreateBufferResource(sizeof(TransformationMatrix));
	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * v, resource_.Vertex.Get(), v);
	if (state->GetUseLight() != NONE)
	{
		resource_.Light = CreateResources::CreateBufferResource(sizeof(LightData));
	}

	uint32_t i = 36;
	resource_.Index = CreateResources::CreateBufferResource(sizeof(uint32_t) * i);
	resource_.IndexBufferView = CreateResources::IndexCreateBufferView(sizeof(uint32_t) * i, resource_.Index.Get());
	state;
}

//10
//23
void ModelCubeState::Draw(Model* state, WorldTransform worldTransform, ViewProjection viewprojection)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;
	uint32_t* indexData = nullptr;

	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));

	Vector4 pos = state->GetCenterPos();
	float size = state->GetSize();

	vertexData[0].position = { pos.x - size,pos.y-size,pos.z+size,pos.w };
	vertexData[0].texcoord = { 0.0f,1.0f };
	vertexData[0].normal = { 0.0f,1.0f,0.0f };
	//20
	//31
	vertexData[1].position = { pos.x + size,pos.y-size,pos.z + size,pos.w };
	vertexData[1].texcoord = { 1.0f,1.0f };
	vertexData[1].normal = { 0.0f,1.0f,0.0f };

	vertexData[2].position = { pos.x + size,pos.y+size,pos.z + size,pos.w };
	vertexData[2].texcoord = { 1.0f,0.0f };
	vertexData[2].normal = { 0.0f,1.0f,0.0f };

	vertexData[3].position = { pos.x - size,pos.y+size,pos.z + size,pos.w };
	vertexData[3].texcoord = { 0.0f,0.0f };
	vertexData[3].normal = { 0.0f,1.0f,0.0f };

	//64
	//75
	vertexData[4].position = { pos.x - size,pos.y + size,pos.z - size,pos.w };
	vertexData[4].texcoord = { 1.0f,0.0f };
	vertexData[4].normal = { 0.0f,1.0f,0.0f };
	
	vertexData[5].position = { pos.x + size,pos.y + size,pos.z - size,pos.w };
	vertexData[5].texcoord = { 0.0f,1.0f };
	vertexData[5].normal = { 0.0f,1.0f,0.0f };

	vertexData[6].position = { pos.x + size,pos.y - size,pos.z - size,pos.w };
	vertexData[6].texcoord = { 1.0f,1.0f };
	vertexData[6].normal = { 1.0f,1.0f,0.0f };

	vertexData[7].position = { pos.x - size,pos.y - size,pos.z - size,pos.w };
	vertexData[7].texcoord = { 0.0f,1.0f };
	vertexData[7].normal = { 0.0f,1.0f,0.0f };

	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 0; indexData[4] = 2; indexData[5] = 3;
	
	indexData[6] = 4; indexData[7] = 5; indexData[8] = 6;
	indexData[9] = 4; indexData[10] = 6; indexData[11] = 7;

	indexData[12] = 0; indexData[13] = 4; indexData[14] = 7;
	indexData[15] = 3; indexData[16] = 4; indexData[17] = 0;

    indexData[18] = 0; indexData[19] = 7; indexData[20] = 6;
	indexData[21] = 1; indexData[22] = 0; indexData[23] = 6;

	indexData[24] = 5; indexData[25] = 3; indexData[26] = 2;
	indexData[27] = 4; indexData[28] = 3; indexData[29] = 5;
	
	indexData[30] = 5; indexData[31] = 2; indexData[32] = 6;
	indexData[33] = 2; indexData[34] = 1; indexData[35] = 6;

	worldTransform.TransfarMatrix(resource_.wvpResource, viewprojection);
	materialData->color = state->GetColor();
	materialData->uvTransform = MatrixTransform::AffineMatrix(state->GetuvScale(), state->GetuvRotate(), state->GetuvTranslate());
	if (state->GetUseLight() != NONE)
	{
		LightData* lightData = nullptr;
		resource_.Light->Map(0, nullptr, reinterpret_cast<void**>(&lightData));

		lightData->color = { 1.0f,1.0f,1.0f,1.0f };
		lightData->direction = { 0.0f,-1.0f,0.0f };
		lightData->intensity = 1.0f;

	}

	CommandCall(state);
}

void ModelCubeState::CommandCall(Model* state)
{

	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty PSO = {};


	PSO = GraphicsPipelineManager::GetInstance()->GetPso().shape;

	//テクスチャがある場合
	if (!state->GetTexHandle() == 0) {
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite3d.none;
	}
	if (state->GetUseLight() == HARF_LAMBERT)
	{
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Herf_Lambert;
	}
	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);
	commands.m_pList->IASetIndexBuffer(&resource_.IndexBufferView);

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commands.m_pList->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	if (!state->GetTexHandle() == 0)
	{
		DescriptorManager::rootParamerterCommand(2, state->GetTexHandle());
	}
	commands.m_pList->SetGraphicsRootConstantBufferView(1, resource_.wvpResource->GetGPUVirtualAddress());
	if (state->GetUseLight() != NONE)
	{
		commands.m_pList->SetGraphicsRootConstantBufferView(3, resource_.Light->GetGPUVirtualAddress());
	}

	commands.m_pList->DrawIndexedInstanced(36 , 1, 0, 0, 0);
}



