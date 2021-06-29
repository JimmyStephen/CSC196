#pragma once

#ifdef DYNAMIC_EXPORTS
#define DYNAMIC_API __declspec(dllexport)
#else
#define DYNAMIC_API __declspec(dllimport)
#endif

namespace nc
{
	struct DYNAMIC_API point
	{
		float x;
		float y;

		point(float x, float y) : x{x}, y{y} {};
		point operator + (point p) {return {p.x + x, p.y + y}; }

	};
}