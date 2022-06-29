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

	void ExplodeSparks(Projectile& p, int size, float deltaTime);
	//void ExplodeSmallProj(int size);

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 TicksCount;

	std::vector<Projectile> vecProjectiles;
	//std::vector<SmallProjectile> vecSmallProjs;
	std::vector<Spark> vecSparks;

	//std::vector<SDL_Rect> vecRect;

	bool IsRunning;
	bool UpdatingFireworks;
	float Delay = 0.0;
};