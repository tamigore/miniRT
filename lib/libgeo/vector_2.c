#include "libgeo.h"

t_v3	v_prod(t_v3 a, t_v3 b)
{
	t_v3 vec;

	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	vec.z = a.z * b.z;
	return (vec);
}

double	v_len(t_v3 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_v3	v_norm(t_v3 vec)
{
	vec.x = vec.x / v_len(vec);
	vec.y = vec.y / v_len(vec);
	vec.z = vec.z / v_len(vec);
	return (vec);
}

double	v_dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
