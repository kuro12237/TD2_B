#include <SlectScene/SlectScene.h>

void SlectStage::Initialize()
{
	uint32_t tex = TextureManager::LoadTexture("Resources/mob.png");
	SpritetexHandle = tex;

	uint32_t Slecttex = TextureManager::LoadTexture("Resources/uvChecker.png");
	SlecttexHandle = Slecttex;

	for (int i = 0; i < SLECTSTAGE_SPRITE_MAX; i++)
	{
		sprite_[i] = make_unique<Sprite>();
		sprite_[i]->SetTexHandle(tex);
		sprite_[i]->SetSrc({ 0.5f,0 }, { 0.75f,0.75f }, { 0,0 }, { 0, 0.75f });//右上右下左上左下
		sprite_[i]->Initialize(new SpriteBoxState, { 100,60 }, { 75,75 });
	}


	int width = 1;
	int height = 1;


	int countWidth = 0;
	int countHeight = 0;
	for (int i = 1; i < SLECTSTAGE_SPRITE_MAX + 1; i++)
	{
		worldTransform_[i - 1].Initialize();



		worldTransform_[i - 1].translate = { (150.0f * countHeight),(150.0f * countWidth),0 };
		countHeight++;

		worldTransform_[i - 1].UpdateMatrix();
		if (i % 8 == 0)
		{
			countWidth++;
			countHeight = 0;
		}
	}

	width++;
	if (width % 15 == 0)
	{
		height++;
		width = 1;
	}

	Slectsprite_ = make_unique<Sprite>();
	Slectsprite_->SetTexHandle(Slecttex);
	Slectsprite_->Initialize(new SpriteBoxState, { 0,0 }, { 75,75 });

	SlectTransform_.Initialize();
	SlectTransform_.scale = { 1,1,0 };
	SlectTransform_.translate = { 100,60 };
	SlectTransform_.UpdateMatrix();

}

void SlectStage::Update(GameManager* Scene)
{
	if (!SlectStage::isUpdate)
	{
		//	return;
		Scene;
	}


	//選ぶ処理
	if (Input::GetInstance()->PushKey(DIK_W) && Input::GetInstance()->PushKeyPressed(DIK_W))
	{
		SlectTransform_.translate.y -= 150.0f;
	}

	if (Input::GetInstance()->PushKey(DIK_S) && Input::GetInstance()->PushKeyPressed(DIK_S))
	{
		SlectTransform_.translate.y += 150.0f;
	}

	if (Input::GetInstance()->PushKey(DIK_A) && Input::GetInstance()->PushKeyPressed(DIK_A))
	{
		SlectTransform_.translate.x -= 150.0f;
	}

	if (Input::GetInstance()->PushKey(DIK_D) && Input::GetInstance()->PushKeyPressed(DIK_D))
	{
		SlectTransform_.translate.x += 150.0f;
	}


	for (int i = 1; i < SLECTSTAGE_SPRITE_MAX; i++)
	{
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE))
		{
			if (SlectTransform_.translate.x > worldTransform_[0].translate.x &&
				SlectTransform_.translate.y > worldTransform_[0].translate.y)
			{
				Scene->ChangeState(new GameScene);
				return;
			}
			
		}
		worldTransform_[i].UpdateMatrix();
	}

	SlectTransform_.UpdateMatrix();


	//ここまで


	//ここにセレクトの処理を書く
	//セレクトの処理は、もう一つ短径やらスプライトを用意して、方向キーやスティックを押したらその座標分プラスマイナスする処理をした後に、
	//その短径orスプライトがステージ1や２のスプライトに当たったかつSPACEを押したら、シーンを変更する処理を書く。
	view.UpdateMatrix();
}



void SlectStage::Back2dSpriteDraw()
{

}

void SlectStage::Object3dDraw()
{


}

void SlectStage::Flont2dSpriteDraw()
{
	for (int i = 0; i < SLECTSTAGE_SPRITE_MAX; i++)
	{
		worldTransform_[i].UpdateMatrix();
		sprite_[i]->Draw(worldTransform_[i]);
	}

	SlectTransform_.UpdateMatrix();
	Slectsprite_->Draw(SlectTransform_);

}