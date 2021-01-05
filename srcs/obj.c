#include "miniRT.h"

t_obj		*object(t_env *env)
{
	t_obj	*obj;

	if (!(obj = malloc(sizeof(t_obj))))
		return (NULL);
	obj->nb = count_obj(env);
	obj->dist = MAX_DEPH;
	obj->color = 0;
	obj->car = NULL;
	obj->pla = NULL;
	obj->tri = NULL;
	obj->cyl = NULL;
	obj->sph = NULL;
	return (obj);
}

int			count_obj(t_env *env)
{
	int		i;

	i = 0;
	i += count_sph(env->sph);
	i += count_car(env->car);
	i += count_pla(env->pla);
	i += count_cyl(env->cyl);
	i += count_tri(env->tri);
	reset_env(&env);
	return (i);
}

void		get_color(t_obj *obj)
{
	if (obj->sph)
		obj->color = rgb2color(obj->sph->R, obj->sph->G, obj->sph->B);
	else if (obj->car)
		obj->color = rgb2color(obj->car->R, obj->car->G, obj->car->B);
	else if (obj->cyl)
		obj->color = rgb2color(obj->cyl->R, obj->cyl->G, obj->cyl->B);
	else if (obj->tri)
		obj->color = rgb2color(obj->tri->R, obj->tri->G, obj->tri->B);
	else if (obj->pla)
		obj->color = rgb2color(obj->pla->R, obj->pla->G, obj->pla->B);
}
