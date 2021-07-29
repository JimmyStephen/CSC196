#include "Actors/Game.h"
#include "Audio/AudioSystem.h"
#include "FileIO/FileIO.h"
#include <iostream>
#include <string>

Game game;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	game.Update(dt);

	//int x, y;
	//Core::Input::GetMousePos(x, y);
	//psPosition.x = static_cast<float>(x);
	//psPosition.y = static_cast<float>(y);
	//
	////follow mouse
	//if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	//{
	//	std::vector<nc::Color> colorsButGood = { nc::Color::red, nc::Color::white, nc::Color::blue };
	//	engine.Get<nc::ParticleSystem>()->Create(psPosition, 100, 2, colorsButGood[rand() % colorsButGood.size()], 150);
	//	engine.Get<nc::AudioSystem>()->PlayAudio("explosion");
	//}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}


int main()
{
	char name[] = "CSC196";
	Core::Init(name, 800, 600, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	game.Initialize();
	Core::GameLoop();
	Core::Shutdown();
}