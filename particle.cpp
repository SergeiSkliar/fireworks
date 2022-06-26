#include "particle.h"
#include <iostream>
using namespace std;

Projectile::Projectile()
{
	p.x = 0;
	p.y = 0;
	//p.speed = RandomNum(50);
	//cout << p.speed << endl;
	p.angle = RandomNum(100.0) - 50.0;
	cout << p.angle << endl;
	p.vx = p.angle;
	p.vy = -100.0;

	p.fuse = RandomNum(2.0);
}

Projectile::Projectile(float _x, float _y)
{
	p.x = _x;
	p.y = _y;
	//p.speed = RandomNum(50) + 100;
	//cout << p.speed << endl;

	p.vx = p.angle * Gravity;
	p.vy = -100.0;

	//p.fuse = RandomNum(2.0);
}


void Projectile::Update(float deltaTime)
{
	//p.lifetime += deltaTime;
	p.x += p.vx * deltaTime;
	p.y += (p.vy + Gravity) * deltaTime;
	//if (p.lifetime <= p.fuse) // TODO refactor float comparison
	//{
		// moving
	//p.speed = RandomNum(200.0);
	//	float angle = RandomNum(2.0 * PI);
	//	p.vx = cosf(angle) * p.speed;
	//	p.vy = sinf(angle) * p.speed;

	//	p.x += p.vx * deltaTime;
	//	p.y += p.vy  * deltaTime ;
	//}
	//else
	//{
	//	// choose explosion type
	//	// 1 - small projectiles
	//	// 2 - sparks
	//	if (!Exploded)
	//	{
	//		Exploded = true;
	//		ExlosionType = RandomNum(1);
	//		if (ExlosionType == 0)
	//		{
	//			ExplodeSparks(RandomNum(100) + 15);
	//		}
	//		else
	//		{
	//			ExplodeSmallProj(RandomNum(2));
	//		}
	//	}
	//}
}

//void Projectile::Draw(SDL_Renderer* renderer)
//{
//	SDL_Rect proj;
//	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
//	SDL_RenderClear(renderer);
//	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//	proj.x = static_cast<int>(p.x - thickness);
//	proj.y = static_cast<int>(p.y - thickness);
//	proj.w = thickness;
//	proj.h = thickness;
//	SDL_RenderFillRect(renderer, &proj);
//	SDL_RenderPresent(renderer);
//
//}

//void Projectile::ExplodeSparks(int size)
//{
//	for (int i = 0; i <= size; ++i)
//	{
//		Spark spark;
//		
//
//	}
//}
//
//void Projectile::ExplodeSmallProj(int size)
//{
//}
//
//Spark::Spark()
//{
//}
//
//Spark::Spark(float _x, float _y)
//{
//	p.x = _x;
//	p.y = _y;
//	p.speed = RandomNum(50);
//
//	p.vx = RandomNum(25);
//	p.vy = -p.speed;
//
//	p.fuse = RandomNum(2.0);
//}
