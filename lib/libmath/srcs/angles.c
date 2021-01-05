#include "libmath.h"

double	rad(int deg)
{
	return (deg * M_PI / FLAT_ANGLE);
}

double	deg(double rad)
{
	return (rad * FLAT_ANGLE / M_PI);
}

double	tan(double x)
{
	return (sin(x) / cos(x));
}
