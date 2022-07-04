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

	void ExplodeProjectile(const Projectile& p, float deltaTime);
	void ExplodeSmallProjectile(const SmallProjectile& sp, float deltaTime);
	//void ExplodeSmallProj(const SmallProjectile& p, int size, float deltaTime);

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 TicksCount;

	std::vector<Projectile> vecProjectiles;
	std::vector<SmallProjectile> vecSmallProjs;
	std::vector<Spark> vecSparks;

	//std::vector<SDL_Rect> vecRect;

	bool IsRunning;
	bool UpdatingFireworks;
	float Delay = 0.0;
};