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

int		sphere_intersect(t_sph *sph, t_ray *ray)
{
	double	t0;
	double	t1;
	double	a;
	double	b;
	double	c;
	t_v3	L;

	L = v_sub(ray->pos, sph->pos);
	a = v_dot(ray->dir, ray->dir);
	b = 2 * v_dot(ray->dir, L);
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
	ray->t = t0;
	return (1);
}

int		plane_intersect(t_env *env, t_ray *ray)
{
	double	t;
	double	d;
	t_v3	dir;
	t_v3	ori;
	t_v3	nor;
	t_v3	bas;

	if (v_dot(ray->dir, env->pla->dir) == 0)
		return (0);
	dir = ray->dir;
	ori = ray->pos;
	nor = env->pla->dir;
	bas = env->pla->pos;
	d = -nor.x * bas.x - nor.y + bas.y - nor.z * bas.z;
	t = (nor.x * ori.x + nor.y * ori.y + nor.z * ori.z + d) /
		(-nor.x * dir.x - nor.y * dir.y - nor.z * dir.z);
//	t = v_dot(v_sub(env->pla->ori, env->ray->ori), env->pla->dir) / v_dot(env->ray->dir, env->pla->dir);
	if (t < 0)
		return (0);
	ray->t = t;
	return (1);
}
