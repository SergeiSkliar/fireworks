#include "particle.h"
#include <iostream>
using namespace std;

Projectile::Projectile()
{
	p.x = 0;
	p.y = 0;
	p.lifetime = 0.0;
	//p.speed = RandomFloat(50);
	//cout << p.speed << endl;
	p.angle = RandomFloat(100.0) - 50.0;
	//cout << p.angle << endl;
	p.vx = p.angle;
	p.vy = -100.0;

	p.fuse = RandomFloat(2.0) + 1.5;
}

Projectile::Projectile(float _x, float _y)
{
	p.x = _x;
	p.y = _y;
	p.lifetime = 0.0;
	//p.speed = RandomFloat(50) + 100;
	//cout << p.speed << endl;
	p.angle = RandomFloat(100.0) - 50.0;

	p.vx = p.angle;
	p.vy = RandomFloat(-150.0) - 100.0; // -100.0 - minimum speed

	p.fuse = RandomFloat(2.0) + 1.5;
}


void Projectile::Update(float deltaTime)
{
	p.lifetime += deltaTime;

	
	if (p.lifetime <= p.fuse) // TODO refactor float comparison
	{
		// moving
	//	p.speed = RandomFloat(200.0);
	//	float angle = RandomFloat(2.0 * PI);
		p.x += p.vx * deltaTime;
		p.y += (p.vy + Gravity) * deltaTime;
	}
	else
	{
		// choose explosion type
		// 1 - small projectiles
		// 2 - sparks
		if (!Exploded)
		{
			Exploded = true;
			//ExlosionType = RandomFloat(1);
			//if (ExlosionType == 0)
			//{
				// ExplodeSparks(p.x,p.y,RandomInt(100) + 15);
			//}
			//else
			//{
			//	ExplodeSmallProj(RandomFloat(2));
			//}
		}
	}
}





Spark::Spark()
{
	spark.x = 0;
	spark.y = 0;
	spark.lifetime = 0.0;

	spark.angle = RandomFloat(2.0 * PI);
	spark.vx = cosf(spark.angle) * spark.speed;
	spark.vy = sinf(spark.angle) * spark.speed;

	spark.fuse = RandomFloat(2.0) + 1.5;
}

Spark::Spark(float _x, float _y)
{
	spark.x = _x;
	spark.y = _y;
	spark.lifetime = 0.0;

	spark.angle = RandomFloat(2.0 * PI);
	//spark.vx = cosf(spark.angle) * spark.speed;
	//spark.vy = sinf(spark.angle) * spark.speed;
	spark.vx = cosf(spark.angle) * 50;
	spark.vy = sinf(spark.angle) * 50;

	spark.fuse = RandomFloat(2.0) + 1.5;
}

Spark::Spark(const Projectile& pa)
{
	spark.x = pa.GetX();
	spark.y = pa.GetY();
	spark.lifetime = 0.0;

	spark.angle = RandomFloat(2.0 * PI);
	//spark.vx = cosf(spark.angle) * spark.speed;
	//spark.vy = sinf(spark.angle) * spark.speed;
	spark.speed = RandomFloat(50.0);
	spark.vx = cosf(spark.angle) * pa.GetLifetime() * spark.speed;
	spark.vy = sinf(spark.angle) * pa.GetLifetime() * spark.speed;

	spark.fuse = pa.GetLifetime() / 2;
}

void Spark::Update(float deltaTime)
{
	spark.lifetime += deltaTime;
	if (spark.lifetime <= spark.fuse) // TODO refactor float comparison
	{
		// moving
		spark.x += spark.vx * deltaTime;
		spark.y += (spark.vy + Gravity) * deltaTime;
	}
	else
	{
		// spark expires
		if (!Expired)
		{
			Expired = true;
		}
	}
}
