#include "Sprite.h"

void Sprite::Initialize(ISpriteState* state, Vector2 pos, Vector2 size)
{
	state_ = state;
	state_->Initialize(this);

	Pos_ = pos;
	size_ = size;
	blendMode_ = BlendNone;

}

void Sprite::Draw(WorldTransform worldTransform)
{
	state_->Draw(this, worldTransform);
}

void Sprite::SetSrc(Vector2 TR, Vector2 BR, Vector2 TL, Vector2 BL)
{
	srcTR = TR;
	srcBR = BR;
	srcTL = TL;
	srcBL = BL;
}

Vector4 Sprite::ColorConversion(uint32_t rgbaValue)
{
	Vector4 result = {};
	result.x = ((rgbaValue >> 24) & 0xFF) / 255.0f; // Red
	result.y = ((rgbaValue >> 16) & 0xFF) / 255.0f; // Green
	result.z = ((rgbaValue >> 8) & 0xFF) / 255.0f;  // Blue
	result.w = (rgbaValue & 0xFF) / 255.0f;         // Alpha
	return result;
}

