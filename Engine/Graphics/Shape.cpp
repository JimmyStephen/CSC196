#include "Shape.h"
#include <fstream>

namespace nc
{
	void Shape::Draw(Core::Graphics& graphics, Vector2 position, float angle, float scale)
	{
		for (size_t i = 0; i < points.size() - 1; i++) {
			nc::Vector2 p1 = position + (Vector2::Rotate(points[i], angle) * scale);
			nc::Vector2 p2 = position + (Vector2::Rotate(points[i + 1], angle) * scale);

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	void Shape::Draw(Core::Graphics& graphics, const Transform& transform)
	{
		graphics.SetColor(color);
		for (size_t i = 0; i < points.size() - 1; i++) {
			//nc::Vector2 p1 = transform.position + (Vector2::Rotate(points[i], transform.rotation) * transform.scale);
			//nc::Vector2 p2 = transform.position + (Vector2::Rotate(points[i + 1], transform.rotation) * transform.scale);

			nc::Vector2 p1 = transform.matrix * points[i];
			nc::Vector2 p2 = transform.matrix * points[i+1];

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	bool Shape::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;

			stream >> color;

			std::string line;
			std::getline(stream, line);
			size_t size = std::stol(line);

			for (size_t i = 0; i < size; i++)
			{
				nc::Vector2 point;
				stream >> point;

				points.push_back(point);
			}
			ComputeRadius();
		}
		return success;
	}

	void Shape::ComputeRadius()
	{
		for (auto& point : points)
		{
			float r = point.Length();
			if (r > radius) radius = r;
		}
	}
}