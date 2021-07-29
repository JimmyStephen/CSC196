#include "core.h"
#include <iostream>
#include <vector>

//int x = 1920;
//int y = 1080;
int sizeX = 800;
int sizeY = 600;

struct Vector2
{
	float x, y;

	Vector2() : x{ 0 }, y{ 0 } {}
	Vector2(float x, float y) : x{ x }, y{ y } {}

	Vector2 operator + (Vector2 v) { return Vector2{ x + v.x, y + v.y }; }
	Vector2 operator * (float s) { return Vector2{ x * s, y * s }; }
	Vector2 operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
	Vector2 operator *= (float s) { x *= s; y *= s; return *this; }
};

Vector2 position{ 400,300 };
std::vector<Vector2> points = { {-50,-50}, {50,-50}, {0,50}, {-50,-50} };
std::vector<Vector2> points2 = { {-50,-50}, {50,-50}, {0,50}, {-50,-50}, {0,-50}, {25,0}, {-25,0}, {0,-50} };
const float speed = 5;
float timer = 0;


bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	timer += dt;
	//follow mouse
	//int x, y;
	//Core::Input::GetMousePos(x, y);
	//position.x = static_cast<float>(x);
	//position.y = static_cast<float>(y);

	//wasd
	Vector2 input;
	if (Core::Input::IsPressed('A')) input.x = -1;
	if (Core::Input::IsPressed('D')) input.x = 1;
	if (Core::Input::IsPressed('W')) input.y = -1;
	if (Core::Input::IsPressed('S')) input.y = 1;

	position += input * speed;

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	//graphics.SetBackgroundColor(RGB(rand() % 255, rand() % 255, rand() % 255));

	//for (int i = 0; i < 1000; i++) {
	//	graphics.SetColor(RGB(rand() % 255, rand() % 255, rand() % 255));
	//	graphics.DrawString(rand() % x, rand() % y, "Just Monika");
	//}
	//for (int i = 0; i < 1000; i++) {
	//	graphics.SetColor(RGB(rand() % 255, rand() % 255, rand() % 255));
	//	graphics.DrawLine(rand() % x, rand() % y, position.x, position.y);
	//}

	// 	  Above Random line going to curser, Below random line to somewere random

	//for (int i = 0; i < 1000; i++) {
	//	graphics.SetColor(RGB(rand() % 255, rand() % 255, rand() % 255));
	//	graphics.DrawLine(rand() % x, rand() % y, rand() % x, rand() % y);
	//}

	//graphics.SetColor(RGB(255, 255, 255));
	//graphics.DrawString(x/2, y/2, "Just Monika");

	//white
	//graphics.SetColor(RGB(255, 255, 255));
	//rainbow
	graphics.SetColor(RGB(rand() % 255, rand() % 255, rand() % 255));

	float scale = 1 + std::sin(timer) * 2;
	for (size_t i = 0; i < points.size() - 1; i++) {
		Vector2 p1 = position + (points[i] * scale);
		Vector2 p2 = position + (points[i + 1] * scale);
		//Vector2 p1{ position.x + points[i].x, position.y + points[i].y };
		//Vector2 p2{ position.x + points[i+1].x, position.y + points[i+1].y };

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

	//graphics.DrawLine(0, 0, points[0].x + position.x, points[0].y + position.y);
	//graphics.DrawLine(x, 0, points[1].x + position.x, points[1].y + position.y);
	//graphics.DrawLine(0, y, points[2].x + position.x, points[2].y + position.y);
	//graphics.DrawLine(x, y, points[2].x + position.x, points[2].y + position.y);
}

int main()
{

	//for (int i = 0; i < 10; i++) {
	//	std::cout << i << " % 3 = " << i % 3 << std::endl;
	//}

	char name[] = "CSC196";
	Core::Init(name, x, y);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	//std::cout << char(92) << char(79) << char(119) << char(79) << char(47) << char(3);
}