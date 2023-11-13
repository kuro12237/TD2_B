#include "DebugScene.h"

DebugScene::~DebugScene()
{
	
}

void DebugScene::Initialize()
{
	DebugCamera* debugCamera = new DebugCamera();
	debugCamera->Initialize();
	DebugTools::addCommand(debugCamera,"DebugCamera");

	viewProjection.Initialize({0,0,0.0f }, { 0.0f,0.0f,-10.0f });

	sprite_ = make_unique<Sprite>();

	SpriteTexHandle_ = TextureManager::LoadTexture("Resources/mob.png");

	uint32_t SpriteTexHandle = TextureManager::LoadTexture("Resources/mob.png");

	SpriteTexHandle = TextureManager::LoadTexture("Resources/CLEYERA.png");

	Audiohandle = AudioManager::SoundLoadWave("Resources/SelectBGM.wav");
	Audiohandle2 = AudioManager::SoundLoadWave("Resources/hit.wav");
	
	sprite_->SetTexHandle(SpriteTexHandle);
	sprite_->Initialize(new SpriteBoxState,{0,0},{320,320});
	
	sprite2_ = make_unique<Sprite>();
	sprite2_->SetTexHandle(SpriteTexHandle);
	sprite2_->Initialize(new SpriteBoxState,{640,0},{320,320});
	
	
	sprite2WorldTransform_.Initialize();
	spriteWorldTransform_.Initialize();
	sprite2WorldTransform_.parent= &spriteWorldTransform_;


	particle_ = make_unique<Particle>();
	particle_->SetTexHandle(SpriteTexHandle);
	particle_->Initialize(new ParticlePlaneState,20);

	
}

void DebugScene::Update(GameManager* Scene)
{
	ImGui::Begin("MainCamera");
	ImGui::SliderFloat3("trans", &viewProjection.translation_.x, -15, 15);
	ImGui::SliderFloat3("rotate", &viewProjection.rotation_.x, -1, 1);
	ImGui::End();

	ImGui::Begin("key");
	ImGui::Text("0 Pushkey PlayAudio");
	ImGui::Text("9 Pushkey StateChange");
	ImGui::End();

	ImGui::Begin("Sprite");
	ImGui::ColorPicker4("color", &color.x);
	ImGui::DragFloat3("Rotate", &sprite2WorldTransform_.translate.x, 0.1f);
	ImGui::Checkbox("NONE", &NoneFlag);
	ImGui::Checkbox("Add", &AddFlag);
	ImGui::Checkbox("Subtract", &SubtractFlag);
	ImGui::Checkbox("Multiply", &MultiplyFlag);
	ImGui::Checkbox("Screen", &ScreenFlag);
	ImGui::End();

	if (Input::GetInstance()->PushKeyPressed(DIK_S))
	{
		AudioManager::AudioPlayWave(Audiohandle);
		Flag = true;
	}
	if (Flag)
	{
		count++;
		//AudioManager::AudioVolumeControl(Audiohandle, count*2);
	}
	if (count>180)
	{
		count = 0;
		AudioManager::AudioStopWave(Audiohandle);
		Flag = false;
	}
	if (Input::GetInstance()->PushKeyPressed(DIK_D))
	{
		AudioManager::AudioPlayWave(Audiohandle2);

	}
	if (Input::GetInstance()->PushKeyPressed(DIK_R))
	{
		Model * model = new Model();
		model->CreateFromObj("MapGround");
		modelWorldTransform_.Initialize();
		models_.push_back(model);
	}

#pragma region 
	{
		if (NoneFlag)
		{
			sprite_->SetBlendMode(BlendNone);
			AddFlag = false;
			SubtractFlag = false;
			MultiplyFlag = false;
			ScreenFlag = false;
		}
		if (AddFlag)
		{
			sprite_->SetBlendMode(BlendAdd);
			NoneFlag = false;
			SubtractFlag = false;
			MultiplyFlag = false;
			ScreenFlag = false;
		}
		if (SubtractFlag)
		{
			sprite_->SetBlendMode(BlendSubtruct);
			AddFlag = false;
			NoneFlag = false;
			MultiplyFlag = false;
			ScreenFlag = false;
		}
		if (MultiplyFlag)
		{
			sprite_->SetBlendMode(BlendMultiply);
			AddFlag = false;
			SubtractFlag = false;
			NoneFlag = false;
			ScreenFlag = false;
		}
		if (ScreenFlag)
		{
			sprite_->SetBlendMode(BlendScreen);
			AddFlag = false;
			SubtractFlag = false;
			MultiplyFlag = false;
			NoneFlag = false;
		}
	}
#pragma endregion

	sprite_->SetColor(color);
	Scene;

	spriteWorldTransform_.UpdateMatrix();
	sprite2WorldTransform_.UpdateMatrix();
	Testparticle();

	
	DebugTools::UpdateExecute(0);
	viewProjection.UpdateMatrix();
	viewProjection = DebugTools::ConvertViewProjection(viewProjection);

}

void DebugScene::Back2dSpriteDraw()
{
}

void DebugScene::Object3dDraw()
{
	particle_->Draw(viewProjection);
	for (Model* &model : models_)
	{
		model->Draw(modelWorldTransform_, viewProjection);
	}
}
void DebugScene::Flont2dSpriteDraw()
{

	sprite_->Draw(spriteWorldTransform_);
	sprite2_->Draw(sprite2WorldTransform_);
}

void DebugScene::Testparticle()
{
	ImGui::Begin("SpownParticle");
	ImGui::SliderFloat3("translate", &TestParticlesTranslate.x, 3.0f, -3.0f);
	ImGui::SliderFloat4("color", &TestParticleColor.x, 1.0f, -0.0f);
	ImGui::End();

	if (Input::GetInstance()->PushKeyPressed(DIK_P))
	{
		Particle_param p1{};
		p1.worldTransform_.Initialize();
		p1.worldTransform_.translate = TestParticlesTranslate;
		p1.color_ = TestParticleColor;
		particle_->PushList(p1);
	}

}


