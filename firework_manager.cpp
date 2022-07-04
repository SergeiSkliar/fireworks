#include "firework_manager.h"
#include <algorithm>
#include <iostream>
using namespace std;


FireworksManager::FireworksManager() :mWindow(nullptr), mRenderer(nullptr), IsRunning(true), TicksCount(0), UpdatingFireworks(false)
{
}

bool FireworksManager::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Fireworks", 100, 100, 1024, 768, 0);
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
		Projectile temp_proj(512.0, 786.0);
		vecProjectiles.push_back(temp_proj);
		std::cout << vecProjectiles.size() << std::endl;
		Spark temp_spark(temp_proj);
	}

	for (auto& p : vecProjectiles)
	{
		p.Update(deltaTime);
		//cout << p.GetX() << endl;
		//cout << p.GetY() << endl;
		if (p.GetStatusofExplosion())
		{
			ExplodeProjectile(p, deltaTime);
		}
	}

	for (auto& sp : vecSmallProjs)
	{
		sp.Update(deltaTime);
		if (sp.IsExploded())
		{
			ExplodeSmallProjectile(sp, deltaTime);
		}
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
	vecSmallProjs.erase(std::remove_if(vecSmallProjs.begin(), vecSmallProjs.end(), [](SmallProjectile& sp) { return sp.IsExploded(); }),
		vecSmallProjs.end());
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
	for (auto& sp : vecSmallProjs)
	{
		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

		SDL_Rect spa;
		spa.x = static_cast<int>(sp.GetX() - thickness);
		spa.y = static_cast<int>(sp.GetY() - thickness);
		spa.w = thickness * 0.75;
		spa.h = thickness * 0.75;
		SDL_RenderFillRect(mRenderer, &spa);
	}
	for (auto& s : vecSparks)
	{
		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

		SDL_Rect spa;
		spa.x = static_cast<int>(s.GetX() - thickness);
		spa.y = static_cast<int>(s.GetY() - thickness);
		spa.w = thickness * 0.75;
		spa.h = thickness * 0.75;
		SDL_RenderFillRect(mRenderer, &spa);
	}
	SDL_RenderPresent(mRenderer);

}

void FireworksManager::ExplodeProjectile(const Projectile& p, float deltaTime)
{
	srand(time(NULL));
	int r = rand() % 2;
	if (r == 0)
	{
		for (int i = 0; i < 20; ++i)
		{
			Spark s(p);
			vecSparks.push_back(s);
		}
	}
	else
	{
		for (int i = 0; i < 2; ++i)
		{
			SmallProjectile sp(p);
			vecSmallProjs.push_back(sp);
		}
	}
}

void FireworksManager::ExplodeSmallProjectile(const SmallProjectile& sp, float deltaTime)
{
	for (int i = 0; i < 20; ++i)
	{
		Spark s(sp);
		vecSparks.push_back(s);
	}
}
