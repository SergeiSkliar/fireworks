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
		Delay = RandomFloat(2.0) + 0.4;
		Projectile temp_proj(512.0, 512.0);
		vecProjectiles.push_back(temp_proj);
		std::cout << vecProjectiles.size() << std::endl;
		Spark temp_spark();
	}

	for (auto& p : vecProjectiles)
	{
		p.Update(deltaTime);
		//cout << p.GetX() << endl;
		//cout << p.GetY() << endl;
	}

	for (auto& s : vecSparks)
	{
		s.Update(deltaTime);
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
	vecSparks.erase(std::remove_if(vecSparks.begin(), vecSparks.end(), [](Spark& s) { return s.IsExpired(); }), 
		vecSparks.end());
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
	for (auto& s : vecSparks)
	{
		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

		SDL_Rect spa;
		spa.x = static_cast<int>(s.GetX() - thickness);
		spa.y = static_cast<int>(s.GetY() - thickness);
		spa.w = thickness / 2;
		spa.h = thickness / 2;
		SDL_RenderFillRect(mRenderer, &spa);
	}
	SDL_RenderPresent(mRenderer);

}
