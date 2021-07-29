#pragma once
#include "Base/Actor.h"

class Player : public nc::Actor
{
public:
	Player(const nc::Transform transform, std::shared_ptr<nc::Shape> shape, float speed);
	virtual void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float immunityFrames = 0.5f;
	float immunityFrameTimer = 0;
	float fireRate = 0.25f;
	float fireTimer;
	float speed{ 300 };
	nc::Vector2 velocity;

};