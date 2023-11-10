#include"SceneChange.h"

SceneChange* SceneChange::GetInstance()
{
	static SceneChange instance;
	return &instance;
}

void SceneChange::Initialize()
{
	uint32_t tex =TextureManager::LoadTexture("Resources/uvChecker.png");
	SceneChange::GetInstance()->texHandle =tex;

	SceneChange::GetInstance()->sprite_ = make_unique<Sprite>();
	SceneChange::GetInstance()->sprite_->SetTexHandle(tex);
	SceneChange::GetInstance()->sprite_->Initialize(new SpriteBoxState, { 0,0 }, { 128,128 });
	SceneChange::GetInstance()->worldTransform_.Initialize();

}

void SceneChange::Update()
{
	//開始処理
	if (SceneChange::GetInstance()->isStart_ == true && SceneChange::GetInstance()->isEnd_ == false)
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
	if (SceneChange::GetInstance()->isStart_ == false && SceneChange::GetInstance()->isEnd_ == true)
	{
		if (EndTimerCount())
		{
			return;
		}

		if (DeSpown())
		{
			SceneChange::GetInstance()->isEnd_ = false;
		}
	}
}

void SceneChange::Draw()
{
	SceneChange::GetInstance()->worldTransform_.UpdateMatrix();
	if (SceneChange::GetInstance()->DrawFlag)
	{
		SceneChange::GetInstance()->sprite_->Draw(SceneChange::GetInstance()->worldTransform_);
	}
}

bool SceneChange::GetScenChangeFlag()
{
	bool result = SceneChange::GetInstance()->SceneChangeFlag;
	SceneChange::GetInstance()->SceneChangeFlag = false;
	return result;
}

bool SceneChange::Spown()
{
	SceneChange::GetInstance()->DrawFlag = true;
	SceneChange::GetInstance()->worldTransform_.scale = VectorTransform::Add(SceneChange::GetInstance()->worldTransform_.scale, { 0.01f,0.01f,0.01f });
	if (SceneChange::GetInstance()->worldTransform_.scale.x>=2.0f)
	{
		return true;
	}
	return false;
}

bool SceneChange::DeSpown()
{
	SceneChange::GetInstance()->worldTransform_.scale = VectorTransform::Subtruct(SceneChange::GetInstance()->worldTransform_.scale, { 0.01f,0.01f,0.01f });
	if (SceneChange::GetInstance()->worldTransform_.scale.x <= 1.0f)
	{
		SceneChange::GetInstance()->DrawFlag = false;
		SceneChange::GetInstance()->EndTimer_ = 0;
		return true;
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

