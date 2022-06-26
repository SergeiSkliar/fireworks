#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include "firework_manager.h"


int main(int argc, char* argv[]) 
{
	FireworksManager fworks;
	bool success = fworks.Initialize();
	if (success)
	{
		fworks.RunLoop();
	}
	fworks.Shutdown();
}
