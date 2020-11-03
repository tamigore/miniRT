#include "miniRT.h"

void	*get_obj(t_env *env, char *txt)
{
	void	*tmp;

	if (ft_strcmp("sph", txt))
		tmp = env->sph;
	else if (ft_strcmp("car", txt))
		tmp = env->car;
	else if (ft_strcmp("cyl", txt))
		tmp = env->cyl;
	else if (ft_strcmp("tri", txt))
		tmp = env->tri;
	else if (ft_strcmp("pla", txt))
		tmp = env->pla;
	else
		tmp = NULL;
	return (tmp);
}

void	get_color(t_obj *obj)
{
	if (obj->sph)
		obj->dist = rgb2color(obj->sph->R, obj->sph->G, obj->sph->B);
	else if (obj->car)
		obj->dist = rgb2color(obj->car->R, obj->car->G, obj->car->B);
	else if (obj->cyl)
		obj->dist = rgb2color(obj->cyl->R, obj->cyl->G, obj->cyl->B);
	else if (obj->tri)
		obj->dist = rgb2color(obj->tri->R, obj->tri->G, obj->tri->B);
	else if (obj->pla)
		obj->dist = rgb2color(obj->pla->R, obj->pla->G, obj->pla->B);
}

void	reset_obj(t_obj *obj)
{
	if (obj->sph)
		obj->sph = NULL;
	if (obj->car)
		obj->car = NULL;
	if (obj->cyl)
		obj->cyl = NULL;
	if (obj->tri)
		obj->tri = NULL;
	if (obj->pla)
		obj->pla = NULL;
}
