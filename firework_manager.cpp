#include "firework_manager.h"
#include <algorithm>
#include <iostream>
using namespace std;


FireworksManager::FireworksManager() :mWindow(nullptr), mRenderer(nullptr), IsRunning(true), TicksCount(0), UpdatingFireworks(false)
{
}

bool FireworksManager::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 2)", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	TicksCount = SDL_GetTicks();

	Projectile first(512.0, 512.0);
	vecProjectiles.push_back(first);


	return true;
}

void FireworksManager::RunLoop()
{
	while (IsRunning)
	{
		ProcessInput();
		UpdateFireworkManager();
		Draw();
	}
}

void FireworksManager::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void FireworksManager::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			IsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		IsRunning = false;
	}
}

void FireworksManager::UpdateFireworkManager()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), TicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - TicksCount) / 1000.0f;

	if (deltaTime > 0.5f)
	{
		deltaTime = 0.5f;
	}
	TicksCount = SDL_GetTicks();

	UpdatingFireworks = true;

	Delay -= deltaTime;

	if (Delay <= 0.1)
	{
		Delay = RandomNum(2.0) + 0.4;
		Projectile temp(512.0, 512.0);
		vecProjectiles.push_back(temp);
		std::cout << vecProjectiles.size() << std::endl;
	}

	for (auto& p : vecProjectiles)
	{
		p.Update(deltaTime);
		//cout << p.GetX() << endl;
		//cout << p.GetY() << endl;
	}

	UpdatingFireworks = false;
	
	//for (auto & p : vecProjectiles)
	//{
	//	p.Update(deltaTime);
	//}

	vecProjectiles.erase(std::remove_if(vecProjectiles.begin(), vecProjectiles.end(), [](Projectile& p) { return p.GetStatusofExplosion(); }), 
		vecProjectiles.end());
}

void FireworksManager::Draw()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
	SDL_RenderClear(mRenderer);
	for (auto& p : vecProjectiles)
	{


		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

		SDL_Rect proj;
		proj.x = static_cast<int>(p.GetX() - thickness);
		proj.y = static_cast<int>(p.GetY() - thickness);
		proj.w = thickness;
		proj.h = thickness;
		SDL_RenderFillRect(mRenderer, &proj);
	}
	SDL_RenderPresent(mRenderer);

}