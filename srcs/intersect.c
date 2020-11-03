#include "miniRT.h"

int			solveQuadratic(float a, float b, float c, double *x0, double *x1)
{
	double	delta;
	double	q;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return 0;
	else if (delta == 0)
	{
		*x0 = - 0.5 * b / a;
		*x1 = - 0.5 * b / a;
	}
	else
	{
		q = (b > 0) ? -0.5 * (b + sqrt(delta)) : -0.5 * (b - sqrt(delta));
		*x0 = q / a;
		*x1 = c / q;
	}
	if (*x0 > *x1)
		swap(x0, x1);
	return (1);
}

int		sphere_intersect(t_sph *sph, t_v3 dir, t_v3 ori, double *t)
{
		double	t0;
		double	t1;
		double	a;
		double	b;
		double	c;
		t_v3	L;

		L = v_sub(ori, v_init(sph->x, sph->y, sph->z));
		a = v_dot(dir, dir);
		b = 2 * v_dot(dir, L);
		c = v_dot(L, L) - (sph->r * sph->r);
		if (!solveQuadratic(a, b, c, &t0, &t1))
			return (0);
		if (t0 > t1)
			swap(&t0, &t1);
		if (t0 < 0)
		{
			t0 = t1;
			if (t0 < 0)
				return (0);
		}
		*t = t0;
		return (1);
}
