#pragma once
#include <cmath>

static constexpr double PI = 3.14159265358979323846;
static constexpr double Gravity = 9;
static constexpr int thickness = 5;


static float RandomNum(float num)
{
	return (rand() / RAND_MAX) * num;
}