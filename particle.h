#pragma once

#include "helper.h"
#include <limits>
#include <SDL.h>

struct Particle
{
	float x = 0.0;
	float y = 0.0;
	float vx = 0.0;
	float vy = 0.0;

	float angle = 0.0;
	float speed = 0.0;
	float lifetime = 0.0;
	float fuse = 0.0;
};

class Projectile
{
public:
	Projectile();
	Projectile(float _x, float _y);
	~Projectile() = default;

	void Update(float deltaTime);
	//void Draw(SDL_Renderer* renderer);
	void ExplodeSparks(float _x, float _y, int size);
	//void ExplodeSmallProj(int size);
	bool GetStatusofExplosion() const { return Exploded; }
	virtual float GetX() const { return p.x; }
	virtual float GetY() const { return p.y; }
	virtual void SetX(float _x) { p.x = _x; }
	virtual void SetY(float _y) { p.y = _y; }
	void SetCoordinates(float _x, float _y) { p.x = _x; p.y = _y; }


private:
	Particle p;
	bool Exploded = false;
	//short ExlosionType = 0;
};
//
//class SmallProjectile : public Projectile
//{
//
//};
//
class Spark : public Projectile
{
public:
	Spark();
	Spark(float _x, float _y);

private:
	Particle spark;
	bool Expired;
};

