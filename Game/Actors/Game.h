#pragma once
#include "Engine.h"


class Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartEndless,
		StartLevel,
		StartEndlessLevel,
		Game,
		GameEndless,
		GameOver,
	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);
	void OnAddPoints(const nc::Event& event);
	void OnPlayerDead(const nc::Event& event);

	void StartLevel();
	void StartEndlessLevel();
	void GameEndless();
public:
	std::unique_ptr<nc::Engine> engine;
	std::unique_ptr<nc::Scene> scene;

private:
	eState state = eState::Title;
	float stateTimer = 0.0f;
	bool destroyedAll = false;
	
	void (Game::* stateFunction)(float) = nullptr;


	size_t score = 0;
	size_t highScore = 0;
	size_t lives = 0;
	size_t gainLife = 1000;

	bool summonRanged = true;
};