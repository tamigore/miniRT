#include "miniRT.h"

int			trace_ray(t_env *env)
{
	int		color;
//	int		shadow;
//	t_v3	P;
//	t_v3	N;
//	t_v3	R;
//	t_ray	*Lray;

	color = 0;
	if (trace(env, env->ray))
	{
//		P = v_add(env->ray->ori, v_multi(env->ray->t, env->ray->dir));
//		N = v_norm(v_sub(P, v_init(env->obj->sph->ori.x, env->obj->sph->ori.y, env->obj->sph->ori.z)));
		color = env->obj->color;// * env->amb->color * env->amb->l;
/*		if (!(Lray = malloc(sizeof(t_ray))))
			return (-1);
		while (env->lum)
		{
//			shadow = 0;
			Lray->dir = v_sub(env->lum->ori, P);
			Lray->ori = P;
			Lray->t = 0;
			R = v_sub(v_multi(2 * v_dot(N, Lray->dir), N), Lray->dir);
			if (trace(env, Lray))
			{
				if (env->ray->t < v_len(env->ray->dir))
					shadow = 1;
			}
//			color += env->lum->l * v_dot(Lray->dir, N) * env->obj->color + env->lum->l * v_dot(R, v_multi(-1, env->ray->dir)) * env->obj->color;
			if (env->lum->next)
				env->lum = env->lum->next;
			else
				break ;
		}
		free(Lray);
*/	}
	env->obj->dist = MAX_DEPH;
	return (color);
}

int			trace(t_env *env, t_ray *ray)
{
	int		hit;

	hit = 0;
	if (trace_sph(env, ray))
		hit = 1;
/*	while (tmp->tri)
		tmp->cyl = tmp->cyl->next;
	while (tmp->cyl)
		tmp->cyl = tmp->cyl->next;
	while (tmp->car)
		tmp->car = tmp->car->next;
*/
	if (trace_pla(env, ray))
		hit = 1;
	reset_env(&env);
	return (hit);
}

int			trace_sph(t_env *env, t_ray *ray)
{
	int		hit;

	hit = 0;
	while (env->sph)
	{
		if ((sphere_intersect(env->sph, ray)))
		{
			if (ray->t < env->obj->dist)
			{
				env->obj->sph = env->sph;
				env->obj->color = env->sph->color;
				env->obj->dist = ray->t;
			}
			hit = 1;
		}
		if (env->sph->next)
			env->sph = env->sph->next;
		else
			break ;
	}
	return (hit);
}

int			trace_pla(t_env *env, t_ray *ray)
{
	int		hit;

	hit = 0;
	while (env->pla)
	{
		if ((plane_intersect(env, ray)))
		{
			if (ray->t < env->obj->dist)
			{
				env->obj->pla = env->pla;
				env->obj->color = env->pla->color;
				env->obj->dist = ray->t;
			}
			hit = 1;
		}
		if (env->pla->next)
			env->pla = env->pla->next;
		else
			break ;
	}
	return (hit);
}
