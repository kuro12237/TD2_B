#include "WorldTransform.h"

void WorldTransform::Initialize()
{
	matWorld = MatrixTransform::Identity();
	
}

void WorldTransform::SRTSetting(Vector3 s, Vector3 r, Vector3 t)
{
	scale = s;
	rotation = r;
	translate = t;
	UpdateMatrix();
}

void WorldTransform::UpdateMatrix()
{
	matWorld = MatrixTransform::AffineMatrix(scale, rotation, translate);
	
	if (parent) {
		matWorld = MatrixTransform::Multiply(matWorld, parent->matWorld);
	}
}

void WorldTransform::TransfarMatrix(ComPtr<ID3D12Resource>& wvpResource, ViewProjection viewProjection, Projection Flag )
{
	TransformationMatrix* wvp = {};
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvp));
	if (Flag == PerspectiveFov)
	{
		matWorld = MatrixTransform::Multiply(matWorld, MatrixTransform::Multiply(viewProjection.matView_, viewProjection.matProjection_));
	}
	if (Flag==OrthographicMatrix)
	{
		Matrix4x4 viewMatrix = MatrixTransform::Identity();
		Matrix4x4 OrthographicMatrix = MatrixTransform::OrthographicMatrix(
			0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 100.0f
		);

		matWorld =MatrixTransform::Multiply(matWorld,MatrixTransform::Multiply(viewMatrix,OrthographicMatrix));
	}
	wvp->WVP = matWorld;
	wvp->world = MatrixTransform::Identity();
	
}
