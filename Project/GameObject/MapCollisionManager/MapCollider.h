#pragma once

class MapCollider
{
public:

	float GetRadious() { return radious_; }
	void SetRadious(float radious) { radious_ = radious; }

	virtual Vector3 GetWorldPosition() = 0;


	Vector2 GetVelocity() { return velocity_; }
	void SetVelocity(Vector2 v) { velocity_ = v; }

	virtual void RightCollision() = 0;
	virtual void LeftCollision() = 0;

	virtual void TopCollision() = 0;
	virtual void DownCollision() = 0;

private:

	float radious_ = 0.5f;

	Vector2 velocity_{};
};

