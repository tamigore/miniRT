#include "miniRT.h"

int			trace_ray(t_env *env, t_ray *ray)
{
	double	color;
	t_v3	Phit;
	t_v3	Nhit;
	double	pattern;

	color = 0;
	if (trace(env))
	{
		Phit = v_add(ray->ori, v_multi(ray->t, ray->dir));
        Nhit = v_norm(v_sub(Phit, v_init(env->sph->ori.x, env->sph->ori.y, env->sph->ori.z)));
		pattern = ((((1 + atan2(Nhit.z, Nhit.x) / M_PI) * 0.5) *  env->sph->r > 0.5) ^
					((acos(Nhit.y) / M_PI) * env->sph->r > 0.5));
		if ((color = MaxVal(4, 0, v_dot(Nhit, v_sub(ray->ori, ray->dir))
			* env->obj->color, env->obj->color * 0.8, pattern)) == NAN)
			return (0);
	}
	return ((int)color);
}

int			trace(t_env *env)
{
	int		hit;

	hit = 0;
	if (trace_sph(env))
	{
//		reset_sph(&(env->sph));
		hit = 1;
	}
/*	while (tmp->tri)
		tmp->cyl = tmp->cyl->next;
	while (tmp->cyl)
		tmp->cyl = tmp->cyl->next;
	while (tmp->car)
		tmp->car = tmp->car->next;
	while (tmp->pla)
		tmp->pla = tmp->pla->next;
*/	get_color(env->obj);
	reset_env(&env);
	return (hit);
}

int			trace_sph(t_env *env)
{
	int		hit;

	hit = 0;
	while (env->sph)
	{
		if ((env->ray->t = sphere_intersect(env->sph, env->ray)) > 0)
		{
			if (env->ray->t < env->obj->dist)
			{
				obj_sph(env, env->obj);
				env->obj->dist = env->ray->t;
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
