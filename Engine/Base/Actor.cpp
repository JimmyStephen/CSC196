#include "Actor.h"
#include "Graphics/Shape.h"
#include <algorithm>

namespace nc
{
	void Actor::Update(float dt)
	{
		transform.Update();
		std::for_each(children.begin(), children.end(), [](auto& child) {child->transform.Update(child->parent->transform.matrix); });
	}

	void Actor::Draw(Core::Graphics& graphics)
	{
		shape->Draw(graphics, transform);
	}
	
	void Actor::AddChild(std::unique_ptr<Actor> actor)
	{
		actor->parent = this;
		children.push_back(std::move(actor));
	}

	float Actor::GetRadius()
	{
		return shape->radius * transform.scale.x;
	}


}