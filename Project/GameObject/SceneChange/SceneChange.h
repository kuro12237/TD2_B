#pragma once
#include"Sprite/Sprite.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"VectorTransform.h"

class SceneChange
{
public:
	SceneChange() {};
	~SceneChange() {};

	static SceneChange* GetInstance();

	static void Initialize();

	static void Update();

	static void Draw();

	static void SetIsStart(bool flag) { SceneChange::GetInstance()->isStart_ = flag; }

	static bool GetScenChangeFlag();
private:

	/// <summary>
	/// 四角の沸き処理
	/// </summary>
	static bool Spown();

	/// <summary>
	/// 四角の削除
	/// </summary>
	static bool DeSpown();

	/// <summary>
	/// 切り替わりの待機時間
	/// </summary>
	static bool EndTimerCount();

	uint32_t texHandle = 0;
	
	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_{};

	bool DrawFlag = false;

	bool isStart_ = false;

	bool isEnd_ = false;

	uint32_t EndTimer_ = 0;
	const uint32_t EndTimerMax_ = 180;

	bool SceneChangeFlag = false;
};

