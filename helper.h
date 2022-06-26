#pragma once
#include <cmath>

static constexpr float PI = 3.14159265358979323846;
static constexpr float Gravity = 9;
static constexpr int thickness = 5;
static constexpr float init_speed = -100.0;


static float RandomFloat(float num)
{
	return ((float)rand() / RAND_MAX) * num;
}

static int RandomInt(int n)
{
	return (rand() / RAND_MAX) * n;
}