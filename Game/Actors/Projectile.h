#pragma once
#include "Base/Actor.h"

class Projectile : public nc::Actor
{
public:
	Projectile(const nc::Transform transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{ speed } {};
	void OnCollision(Actor* actor) override;
	virtual void Update(float dt) override;
private:
	float lifetime{ 2 };
	float speed{ 300 };
};