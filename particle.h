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

	virtual void Update(float deltaTime);

	virtual bool GetStatusofExplosion() const { return Exploded; }
	virtual float GetX() const { return p.x; }
	virtual float GetY() const { return p.y; }
	virtual void SetX(float _x) { p.x = _x; }
	virtual void SetY(float _y) { p.y = _y; }
	float GetAngle() const { return p.angle; }
	float GetLifetime() const { return p.lifetime; }
	float GetFuse() const { return p.fuse; }
	//void SetCoordinates(float _x, float _y) { p.x = _x; p.y = _y; }


private:
	Particle p;
	bool Exploded = false;
	//short ExlosionType = 0;
};

class SmallProjectile : public Projectile
{
public:
	SmallProjectile();
	SmallProjectile(const Projectile& pa);
	~SmallProjectile() = default;

	void Update(float deltaTime) override;
	bool IsExploded() { return Exploded; }

	bool IsExploded() const { return Exploded; }
	bool GetStatusofExplosion() const { return Exploded; }
	float GetX() const { return sp.x; }
	float GetY() const { return sp.y; }
	void SetX(float _x) { sp.x = _x; }
	void SetY(float _y) { sp.y = _y; }
	float GetAngle() const { return sp.angle; }
	float GetLifetime() const { return sp.lifetime; }
	float GetFuse() const { return sp.fuse; }
private:
	Particle sp;
	bool Exploded = false;
};

class Spark : public Projectile
{
public:
	Spark();
	Spark(const Projectile& pa);
	~Spark() = default;

	virtual float GetX() const { return spark.x; }
	virtual float GetY() const { return spark.y; }
	virtual void SetX(float _x) { spark.x = _x; }
	virtual void SetY(float _y) { spark.y = _y; }

	bool IsExpired() const { return Expired; }
	void Update(float deltaTime) override;
private:
	Particle spark;
	bool Expired = false;
};

