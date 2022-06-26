#include "particle.h"

Projectile::Projectile()
{
	p.x = 0;
	p.y = 0;
	p.speed = RandomNum(50);

	p.vx = RandomNum(25);
	p.vy = -p.speed;

	p.fuse = RandomNum(2.0);
}

Projectile::Projectile(float _x, float _y)
{
	p.x = _x;
	p.y = _y;
	p.speed = RandomNum(50);

	p.vx = RandomNum(25);
	p.vy = -p.speed;

	p.fuse = RandomNum(2.0);
}


void Projectile::Update(float deltaTime)
{
	//p.lifetime += deltaTime;

	if (p.lifetime <= p.fuse) // TODO refactor float comparison
	{
		// moving
		float angle = RandomNum(2.0 * PI);
		p.vx = cosf(angle);
		p.vy = sinf(angle);

		p.x += p.vx * Gravity;
		p.y += p.vy * Gravity;
	}
	else
	{
		// choose explosion type
		// 1 - small projectiles
		// 2 - sparks
		if (!Exploded)
		{
			Exploded = true;
			ExlosionType = RandomNum(1);
			if (ExlosionType == 0)
			{
				ExplodeSparks(RandomNum(100) + 15);
			}
			else
			{
				ExplodeSmallProj(RandomNum(2));
			}
		}
	}
}

void Projectile::ExplodeSparks(int size)
{
	for (int i = 0; i <= size; ++i)
	{
		Spark spark;
		

	}
}

void Projectile::ExplodeSmallProj(int size)
{
}

Spark::Spark()
{
}

Spark::Spark(float _x, float _y)
{
	p.x = _x;
	p.y = _y;
	p.speed = RandomNum(50);

	p.vx = RandomNum(25);
	p.vy = -p.speed;

	p.fuse = RandomNum(2.0);
}
