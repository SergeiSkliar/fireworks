#pragma once
#include "particle.h"
#include <vector>
#include <SDL.h>
#include <iostream>

class FireworksManager
{
public:
	FireworksManager();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	void ProcessInput();
	void UpdateFireworkManager();
	void Draw();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 TicksCount;

	std::vector<Projectile> vecProjectiles;
	std::vector<SmallProjectile> vecSmallProjs;
	std::vector<Spark> vecSparks;

	bool IsRunning;
	float Delay = 0.0;
};