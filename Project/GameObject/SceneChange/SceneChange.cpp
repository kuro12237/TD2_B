#include"SceneChange.h"

SceneChange* SceneChange::GetInstance()
{
	static SceneChange instance;
	return &instance;
}

void SceneChange::Initialize()
{
	uint32_t Logotex =TextureManager::LoadTexture("Resources/SceneChangeLogoTex.png");
	uint32_t Titletex = TextureManager::LoadTexture("Resources/SceneChangeTitleTex.png");
	SceneChange::GetInstance()->texHandle =Logotex;

	
	for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
	{
		SceneChange::GetInstance()->isScaleFlag_[i] = false;
		SceneChange::GetInstance()->sprite_[i] = make_unique<Sprite>();
		SceneChange::GetInstance()->sprite_[i]->Initialize(new SpriteBoxState, { 0,0 }, { 128,128 });
	
		SceneChange::GetInstance()->sprite_[i]->SetTexHandle(Logotex);
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
		if (width % 12 == 0)
		{
			height++;
			width = 1;
		}
	}

	width = 0;
	for (int i = 0; i < SCENECHANGE_SPRITE_MAX ; i++)
	{
		if (i % 2 == 0)
		{
			SceneChange::GetInstance()->sprite_[i + 1]->SetTexHandle(Titletex);
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

bool SceneChange::GetEndChandeFlag()
{
	if (!SceneChange::GetInstance()->isEnd_&&
		!SceneChange::GetInstance()->isUpdate)
	{
		return true;
	}

	
	return false;
}

bool SceneChange::Spown()
{
	const float ScaleAddSpeed = 0.075f;

	for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
	{
		SceneChange::GetInstance()->DrawFlag = true;
		SceneChange::GetInstance()->worldTransform_[i].scale = VectorTransform::Add(SceneChange::GetInstance()->worldTransform_[i].scale, { ScaleAddSpeed, ScaleAddSpeed, ScaleAddSpeed });
	
		if (SceneChange::GetInstance()->worldTransform_[i].scale.x > 1.0f|| SceneChange::GetInstance()->worldTransform_[i].scale.y > 1.0f|| SceneChange::GetInstance()->worldTransform_[i].scale.z > 1.0f)
		{
			SceneChange::GetInstance()->worldTransform_[i].scale = {1,1,1};
			SceneChange::GetInstance()->isScaleFlag_[i] = true;
		}
	}
	uint32_t count = 0;

	for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
	{
		if (SceneChange::GetInstance()->isScaleFlag_[i])
		{
			count++;
		}

		if (count==SCENECHANGE_SPRITE_MAX)
		{
			return true;
		}
	}

	return false;
}

bool SceneChange::DeSpown()
{
	const float ScaleAddSpeed = 0.05f;

	for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
	{
		SceneChange::GetInstance()->worldTransform_[i].scale = VectorTransform::Subtruct(SceneChange::GetInstance()->worldTransform_[i].scale, { ScaleAddSpeed, ScaleAddSpeed, ScaleAddSpeed });

		if (SceneChange::GetInstance()->worldTransform_[i].scale.x <= 0.0f || SceneChange::GetInstance()->worldTransform_[i].scale.y <= 0.0f || SceneChange::GetInstance()->worldTransform_[i].scale.z <= 0.0f)
		{
			SceneChange::GetInstance()->isScaleFlag_[i] = false;
			SceneChange::GetInstance()->worldTransform_[i].scale = {0,0,0};
			SceneChange::GetInstance()->DrawFlag = false;
			SceneChange::GetInstance()->EndTimer_ = 0;
			
		}
	}

	uint32_t count = 0;
	for (int i = 0; i < SCENECHANGE_SPRITE_MAX; i++)
	{
		if (!SceneChange::GetInstance()->isScaleFlag_[i])
		{
			count++;
		}
		if (count == SCENECHANGE_SPRITE_MAX)
		{
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

