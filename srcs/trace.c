#include "miniRT.h"

int			trace(t_env *env, t_v3 orig, t_v3 dir)
{
	int		hit;
	double	t;

	hit = 0;
	t = 0;
	if (trace_sph(env->sph, env->obj, &t, dir, orig))
		hit = 1;
/*	while (tmp->tri)
		tmp->cyl = tmp->cyl->next;
	while (tmp->cyl)
		tmp->cyl = tmp->cyl->next;
	while (tmp->car)
		tmp->car = tmp->car->next;
	while (tmp->pla)
		tmp->pla = tmp->pla->next;
*/	get_color(env->obj);
	return (hit);
}

int		trace_sph(t_sph *sph, t_obj *obj, double *t, t_v3 dir, t_v3 ori)
{
	int		hit;

	hit = 0;
	while (sph)
	{
		if ((*t = sphere_intersect(sph, ori, dir, t)) > 0)
		{
			if (*t > obj->dist)
			{
				obj->dist = *t;
				reset_obj(obj);
				obj->sph = sph;
			}
			hit = 1;
		}
		sph = sph->next;
	}
	return (hit);
}
