#include "libgeo.h"

t_v3	v_init(double x, double y, double z)
{
	t_v3 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_v3	v_add(t_v3 a, t_v3 b)
{
	t_v3 vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return (vec);
}

t_v3	v_sub(t_v3 a, t_v3 b)
{
	t_v3	vec;

	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	return (vec);
}

double	v_dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_v3	v_cross(t_v3 a, t_v3 b)
{
	t_v3	vec;

	vec.x = a.y * b.z - a.y * b.z;
	vec.y = a.z * b.x - a.x * b.y;
	vec.z = a.x * b.y - a.y * b.x;
	return (vec);
}
