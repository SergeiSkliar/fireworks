#pragma once

#include "helper.h"
#include <limits>

struct Particle
{
	float x = 0.0;
	float y = 0.0;
	float vx = 0.0;
	float vy = 0.0;

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
	void ExplodeSparks(int size);
	void ExplodeSmallProj(int size);
	bool GetStatusofExplosion() const { return Exploded; }
	float GetX() const { return p.x; }
	float GetY() const { return p.y; }

private:
	Particle p;
	bool Exploded = false;
	short ExlosionType = 0;
};

class SmallProjectile : public Projectile
{

};

class Spark : public Projectile
{
public:
	Spark();
	Spark(float _x, float _y);

private:
	Particle p;
};

