#include "SpriteBoxState.h"

void SpriteBoxState::Initialize(Sprite* state)
{
	resource_.Vertex = CreateResources::CreateBufferResource(sizeof(VertexData) * VertexSize);
	resource_.Material = CreateResources::CreateBufferResource(sizeof(Material));
	resource_.wvpResource = CreateResources::CreateBufferResource(sizeof(TransformationMatrix));
	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * VertexSize, resource_.Vertex.Get(), VertexSize);
	resource_.Index = CreateResources::CreateBufferResource(sizeof(uint32_t) * IndexSize);
	resource_.IndexBufferView = CreateResources::IndexCreateBufferView(sizeof(uint32_t) * IndexSize, resource_.Index.Get());
	state;
}

void SpriteBoxState::Draw(Sprite* state, WorldTransform worldTransform)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;
	uint32_t* indexData = nullptr;
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	Vector2 pos = state->GetPos();
	Vector2 size = state->GetSize();
	
	size = { size.x / 2,size.y / 2 };

	vertexData[0].position = { pos.x-size.x,pos.y+size.y,0,1 };
	vertexData[0].texcoord = state->GetSrcBL();
	
	vertexData[1].position = { pos.x-size.x ,pos.y-size.y,0,1 };
	vertexData[1].texcoord = state->GetSrcTL();


	vertexData[2].position = { pos.x + size.x,pos.y+size.y,0,1 };
	vertexData[2].texcoord = state->GetSrcBR();

	vertexData[3].position = { pos.x + size.x,pos.y-size.y,0,1 };
	vertexData[3].texcoord = state->GetSrcTR();


	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;

	materialData->color = state->GetColor();
	materialData->uvTransform = MatrixTransform::AffineMatrix(state->GetuvScale(), state->GetuvRotate(), state->GetuvTranslate());


	ViewProjection viewprojection = {};

	worldTransform.TransfarMatrix(resource_.wvpResource,viewprojection,OrthographicMatrix);

	CommandCall(state->GetTexHandle(),state);

}
SPSOProperty SpriteBoxState::Get2dSpritePipeline(Sprite* state)
{
	SPSOProperty PSO = {};

	switch (state->GetBlendMode())
	{
	case BlendNone:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.none;
		break;
	case BlendAdd:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.Add;
		break;
	case BlendSubtruct:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.Subtruct;
		break;
	case BlendMultiply:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.Multiply;
		break;
	case BlendScreen:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.Screen;
		break;

	default:
		break;
	}
	return PSO;
}
void SpriteBoxState::CommandCall(uint32_t texHandle,Sprite* state)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	SPSOProperty PSO = {};

	if (texHandle == 0)
	{
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().shape;
	}
	else if (!texHandle == 0)
	{
		PSO = Get2dSpritePipeline(state);
	}


	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);
	commands.m_pList->IASetIndexBuffer(&resource_.IndexBufferView);

	//�`���ݒ�BPSO�ɐݒ肵�Ă����̂Ƃ͂܂��ʁB������̂�ݒ肷��ƍl���Ă����Ηǂ�
	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�}�e���A��CBuffer�̏ꏊ��ݒ�
	commands.m_pList->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	//wvp�p��CBuffer�̏ꏊ��ݒ�
	commands.m_pList->SetGraphicsRootConstantBufferView(1, resource_.wvpResource->GetGPUVirtualAddress());

	if (!texHandle == 0)
	{
		DescriptorManager::rootParamerterCommand(2, texHandle);
	}

	//�`��(DrawCall/�h���[�R�[��)�B
	commands.m_pList->DrawIndexedInstanced(IndexSize, 1, 0, 0, 0);


}
