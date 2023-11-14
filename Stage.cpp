#include "Stage.h"

void Stage::Initilize()
{
	worldTransform_.Initialize();

	worldTransform_.translate.y = 1;

	worldTransform_.UpdateMatrix();


	model_ = make_unique<Model>();
	model_->UseLight(HARF_LAMBERT);
	model_->Initialize(new ModelSphereState);
	texHandle_ = TextureManager::LoadTexture("Resources/uvChecker.png");
	model_->SetTexHandle(texHandle_);
	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionAttributeEnemy);

	/*Map[8][8] = {
		1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
	};*/

}

void Stage::Updata()
{
	/*model_->SetColor({ 1,1,1,1 });

	MapCountX = sizeof(Map[0]) / sizeof(Map[0][0]);
	MapCountY = sizeof(Map) / sizeof(Map[0]);

	if (Map[Player_->GetplayerVertex_().RightTopY_][Player_->GetplayerVertex_().RightTopX_] == BLOCK
		&& Map[Player_->GetplayerVertex_().RightBottomY_][Player_->GetplayerVertex_().RightBottomX_] == BLOCK)
	{
		false;
	}*/

}


void Stage::Draw(ViewProjection view)
{
	for (int y = 0; y < MapCountY; y++)
	{
		for (int x = 0; x < MapCountX; x++)
		{
			if (Map[y][x] == BLOCK)
			{
				model_->Draw(worldTransform_,view);
			}
		}
	}


}
