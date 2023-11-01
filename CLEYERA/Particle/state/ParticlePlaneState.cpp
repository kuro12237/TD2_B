#include"ParticlePlaneState.h"

void ParticlePlaneState::Initialize(Particle* state)
{
	if (NumInstansing)
	{
		//NumInstansingInitialize�����Ăяo���ꂽ��Error���o��
		LogManager::Log("Particle Instansing Error");
		assert(0);
	}
	NumInstansing = state->GetNumInstancing();
	NumInstansingLock = true;

	resource_.instancingResource = CreateResources::CreateBufferResource(sizeof(ParticleData) * NumInstansing);
	dsvIndex = DescriptorManager::CreateInstancingSRV(NumInstansing, resource_.instancingResource, sizeof(ParticleData));

	resource_.Vertex = CreateResources::CreateBufferResource(sizeof(VertexData) * VertexSize);
	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * VertexSize, resource_.Vertex.Get(), VertexSize);
	resource_.Material = CreateResources::CreateBufferResource(sizeof(Material));
	resource_.Index = CreateResources::CreateBufferResource(sizeof(uint32_t) * IndexSize);
	resource_.IndexBufferView = CreateResources::IndexCreateBufferView(sizeof(uint32_t) * IndexSize, resource_.Index.Get());
}

void ParticlePlaneState::Draw(Particle* state,list<Particle_param>param,ViewProjection viewprojection)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;
	uint32_t* indexData = nullptr;
	ParticleData* instansingData = nullptr;

	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	resource_.instancingResource->Map(0, nullptr, reinterpret_cast<void**>(&instansingData));

	vertexData[0].position = { pos.x - size,pos.y + size,pos.z ,pos.w };
	vertexData[0].texcoord = { 0.0f,0.0f };//00
	vertexData[0].normal = { 0.0f,1.0f,0.0f };

	vertexData[1].position = { pos.x + size,pos.y + size,pos.z ,pos.w };
	vertexData[1].texcoord = { 1.0f,0.0f };//10
	vertexData[1].normal = { 0.0f,1.0f,0.0f };

	vertexData[2].position = { pos.x - size,pos.y - size,pos.z,pos.w };
	vertexData[2].texcoord = { 0.0f,1.0f };//01
	vertexData[2].normal = { 0.0f,1.0f,0.0f };

	vertexData[3].position = { pos.x + size,pos.y - size,pos.z,pos.w };
	vertexData[3].texcoord = { 1.0f,1.0f };//11
	vertexData[3].normal = { 0.0f,1.0f,0.0f };

	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;

	materialData->color = { 1,1,1,1 };
	materialData->color = testColor;
	materialData->uvTransform = MatrixTransform::AffineMatrix({1,1,1}, {0,0,0},{0,0,0});
	
	//Billbord�̌v�Z
	CarmeraBillbord(viewprojection);
	
	NumDrawInstansing = 0;

	for (list<Particle_param>::iterator particleIterator = param.begin();
		particleIterator != param.end(); ++particleIterator){

		//�X�P�[�����o��
		sMat = MatrixTransform::ScaleMatrix((*particleIterator).worldTransform_.scale);
		//���s�ړ��ړ�
		tMat = MatrixTransform::TranslateMatrix((*particleIterator).worldTransform_.translate);
		//Affine�ϊ�
		Matrix4x4 matWorld = MatrixTransform::Multiply(sMat, MatrixTransform::Multiply(billboardMatrix, tMat));
		//view�ϊ�
		matWorld = MatrixTransform::Multiply(matWorld, MatrixTransform::Multiply(viewprojection.matView_, viewprojection.matProjection_));
		//uv��Affine
		(*particleIterator).uvTransform_.UpdateMatrix();
		//���
		instansingData[NumDrawInstansing].WVP = matWorld;
		instansingData[NumDrawInstansing].world = MatrixTransform::Identity();
		instansingData[NumDrawInstansing].color = (*particleIterator).color_;
		instansingData[NumDrawInstansing].uvTransform = (*particleIterator).uvTransform_.matWorld;
		NumDrawInstansing++;
	}

	CommandCall(state->GetTexhandle(),state);
}


void ParticlePlaneState::CarmeraBillbord(ViewProjection view)
{
	//��]
	Matrix4x4 backToFrontMatrix = MatrixTransform::Identity();
	Matrix4x4 rm = MatrixTransform::RotateXYZMatrix(view.rotation_.x, view.rotation_.y, view.rotation_.z);

	billboardMatrix = MatrixTransform::Multiply(backToFrontMatrix, rm);
	billboardMatrix.m[3][0] = 0.0f;
	billboardMatrix.m[3][1] = 0.0f;
	billboardMatrix.m[3][2] = 0.0f;
}

void ParticlePlaneState::CommandCall(uint32_t TexHandle,Particle *state)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty pso = Get3dParticlePipeline(state);
	
	commands.m_pList->SetGraphicsRootSignature(pso.rootSignature.Get());
	commands.m_pList->SetPipelineState(pso.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);
	commands.m_pList->IASetIndexBuffer(&resource_.IndexBufferView);

	//�`���ݒ�BPSO�ɐݒ肵�Ă�����̂Ƃ͂܂��ʁB�������̂�ݒ肷��ƍl���Ă����Ηǂ�
	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�}�e���A��CBuffer�̏ꏊ��ݒ�
	commands.m_pList->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	DescriptorManager::rootParamerterCommand(1, dsvIndex);
	DescriptorManager::rootParamerterCommand(2, TexHandle);
	
	commands.m_pList->DrawIndexedInstanced(IndexSize,NumDrawInstansing, 0, 0, 0);
}


SPSOProperty ParticlePlaneState::Get3dParticlePipeline(Particle* state)
{
	SPSOProperty PSO = {};

	switch (state->GetBlendMode())
	{
	case BlendNone:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Particle3d.none;
		break;
	case BlendAdd:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Particle3d.Add;
		break;
	case BlendSubtruct:
		assert(0);
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.Subtruct;
		break;
	case BlendMultiply:
		assert(0);
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.Multiply;
		break;
	case BlendScreen:
		assert(0);
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.Screen;
		break;

	default:
		break;
	}
	return PSO;
}