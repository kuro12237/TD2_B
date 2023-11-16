#include"SceneChange.h"

SceneChange* SceneChange::GetInstance()
{
	static SceneChange instance;
	return &instance;
}

void SceneChange::Initialize()
{
	uint32_t tex =TextureManager::LoadTexture("Resources/uvChecker.png");
	SceneChange::GetInstance()->texHandle = tex;

	for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
	{
		SceneChange::GetInstance()->sprite_[i] = make_unique<Sprite>();
		SceneChange::GetInstance()->sprite_[i]->SetTexHandle(tex);
		SceneChange::GetInstance()->sprite_[i]->Initialize(new SpriteBoxState, { 0,0 }, { 128,128 });
	}

	int width = 1;
	int height = 1;

	for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
	{
	
		SceneChange::GetInstance()->worldTransform_[i].Initialize();
		SceneChange::GetInstance()->worldTransform_[i].scale = { 0,0,0 };
		SceneChange::GetInstance()->worldTransform_[i].translate = { 128.0f * width-64.0f,128.0f * height-64.0f,0 };
		SceneChange::GetInstance()->worldTransform_[i].UpdateMatrix();
		width++;
		if (width % 11 == 0)
		{
			height++;
			width = 1;
		}
	}
}

void SceneChange::Update()
{	
	if (!SceneChange::GetInstance()->isUpdate)
	{
		return;
	}

	//開始処理
	if (SceneChange::GetInstance()->isStart_ == true &&SceneChange::GetInstance()->isEnd_==false)
	{
		//スポーン処理開始
		if (Spown())
		{
			SceneChange::GetInstance()->SceneChangeFlag = true;
			SceneChange::GetInstance()->isStart_ = false;
			SceneChange::GetInstance()->isEnd_ = true;
		}
	}
	//終了処理
	if (SceneChange::GetInstance()->isEnd_ == true && SceneChange::GetInstance()->isStart_ == false)
	{
		if (EndTimerCount())
		{
			return;
		}
	
		if (DeSpown())
		{
			SceneChange::GetInstance()->isEnd_ = false;
			SceneChange::GetInstance()->isUpdate = false;
		}
	}

}

void SceneChange::Draw()
{
	if (SceneChange::GetInstance()->DrawFlag)
	{	
		for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
		{
			SceneChange::GetInstance()->worldTransform_[i].UpdateMatrix();
			SceneChange::GetInstance()->sprite_[i]->Draw(SceneChange::GetInstance()->worldTransform_[i]);
		}
    }
}

void SceneChange::ChangeStart()
{
	if (!SceneChange::GetInstance()->isUpdate)
	{
		SceneChange::GetInstance()->isUpdate = true;
		SceneChange::GetInstance()->isStart_ = true;
	}
}

bool SceneChange::GetisSceneUpdate()
{
	if (SceneChange::GetInstance()->isUpdate)
	{
		return true;
	}

	return false;
}

bool SceneChange::GetScenChangeFlag()
{
	bool result = SceneChange::GetInstance()->SceneChangeFlag;
	SceneChange::GetInstance()->SceneChangeFlag = false;
	return result;
}

bool SceneChange::Spown()
{
	const float ScaleAddSpeed = 0.01f;

	for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
	{
		SceneChange::GetInstance()->DrawFlag = true;
		SceneChange::GetInstance()->worldTransform_[i].scale = VectorTransform::Add(SceneChange::GetInstance()->worldTransform_[i].scale, { ScaleAddSpeed, ScaleAddSpeed, ScaleAddSpeed });
	
		if (SceneChange::GetInstance()->worldTransform_[i].scale.x >= 1.0f|| SceneChange::GetInstance()->worldTransform_[i].scale.y >= 1.0f|| SceneChange::GetInstance()->worldTransform_[i].scale.z >= 1.0f)
		{
			SceneChange::GetInstance()->worldTransform_[i].scale = {1,1,1};
			return true;
		}
	}

	return false;
}

bool SceneChange::DeSpown()
{
	const float ScaleAddSpeed = 0.01f;

	for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
	{
		SceneChange::GetInstance()->worldTransform_[i].scale = VectorTransform::Subtruct(SceneChange::GetInstance()->worldTransform_[i].scale, { ScaleAddSpeed, ScaleAddSpeed, ScaleAddSpeed });

		if (SceneChange::GetInstance()->worldTransform_[i].scale.x <= 0.0f || SceneChange::GetInstance()->worldTransform_[i].scale.y <= 0.0f || SceneChange::GetInstance()->worldTransform_[i].scale.z <= 0.0f)
		{
			SceneChange::GetInstance()->worldTransform_[i].scale = {0,0,0};
			SceneChange::GetInstance()->DrawFlag = false;
			SceneChange::GetInstance()->EndTimer_ = 0;
			return true;
		}
	}
	return false;
}

bool SceneChange::EndTimerCount()
{
	SceneChange::GetInstance()->EndTimer_++;
	if (SceneChange::GetInstance()->EndTimer_ >= SceneChange::GetInstance()->EndTimerMax_)
	{
		return false;
	}
	return true;
}

