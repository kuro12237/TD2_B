#include "PlayerCamera.h"

void PlayerCamera::Initialize()
{
}

void PlayerCamera::Update(Vector3 translate)
{


	viewProj_.translation_ = translate;
	viewProj_.rotation_.x = 0.2f;

	Vector3 offset = offset_;
	Vector3 Lerp = VectorTransform::Lerp(translate,viewProj_.translation_, 1.0f);

	Matrix4x4 rotateXMatrix = MatrixTransform::RotateXMatrix(viewProj_.rotation_.x);
	Matrix4x4 rotateYMatrix = MatrixTransform::RotateYMatrix(viewProj_.rotation_.y);
	Matrix4x4 rotateZMatrix = MatrixTransform::RotateZMatrix(viewProj_.rotation_.z);
	Matrix4x4 rotateMatrix = MatrixTransform::Multiply(rotateXMatrix, MatrixTransform::Multiply(rotateYMatrix, rotateZMatrix));
	
	offset = VectorTransform::TransformNormal(offset, rotateMatrix);
	viewProj_.translation_ = VectorTransform::Add(Lerp, offset);

	viewProj_.UpdateMatrix();

}
