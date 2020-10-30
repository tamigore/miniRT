#include "miniRT.h"
/*
int			color_sph(t_env *env, t_v3 O, t_v3 D)
{
	t_v3	C;
	t_v3	OC;
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	delta;

	C = v_init(env->sph->x, env->sph->y, env->sph->z);
	OC = v_sub(C, O);
	a = v_dot(D, D);
	b = 2 * v_dot(OC, D);
	c = v_dot(OC, OC) - (env->sph->d / 2) * (env->sph->d / 2);
	delta = b*b - 4 * a * c;
	if (delta < 0)
		return (0);
	else if (delta == 0)
	{
		t1 = -b / (2 * a);
	}
	t1 = (-b + sqrt(delta)) / (2 * a);
	t2 = (-b - sqrt(delta)) / (2 * a);
	if (t1 > 1 && t1 <= t2)
		return (rgb2color(env->sph->R, env->sph->G, env->sph->B));
	else if (t2 > 1 && t2 <= t1)
		return (rgb2color(env->sph->R, env->sph->G, env->sph->B));
	else
		return (0);
}
*/
int			trace(t_env *env, t_v3 orig, t_v3 dir, double tNear, t_env *hitObj)
{
	int		hit;
	int		i;
	double	t;
	t_env	*tmp;

	hit = 0;
	i = 0;
	tmp = env;
	t = MAX_DEPH;
	i = count_obj(env);
	while (i-- > 0)
	{
		if (vectorintersect(orig, dir, t) && t < tNear)
		{
			hit = iter->get();
			tNear = t; 
		}
	}
	return (hit);
}



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

int	sphere_intersect(t_env *env, t_v3 dir, t_v3 orig, t_v3 center, double *t)
{
		double	t0;
		double	t1;
		double	a;
		double	b;
		double	c;
		t_v3	L;

		L = v_sub(orig, center);
		a = v_dot(dir, dir);
		b = 2 * v_dot(dir, L);
		c = v_dot(L, L) - (env->sph->r * env->sph->r);
		if (!solveQuadratic(a, b, c, &t0, &t1))
			return (0);
		if (t0 > t1)
			swap(&t0, &t1);
		if (t0 < 0)
		{
            t0 = t1; // if t0 is negative, let's use t1 instead 
            if (t0 < 0)
				return (0); // both t0 and t1 are negative 
        }
        *t = t0;
        return (1); 
}
