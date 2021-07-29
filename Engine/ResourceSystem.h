#pragma once
#include <string>
#include <memory>
#include <algorithm>
#include <map>

namespace nc
{
	class Resource
	{
		virtual bool Load(const std::string& filename) = 0;
	}

	class ResourceSystem : public System
	{
		virtual void Startup() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;
	};
}