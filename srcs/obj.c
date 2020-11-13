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
	while (env->sph)
	{
		if (env->sph->next)
			env->sph = env->sph->next;
		else
			break ;
		i++;
	}
	while (env->car)
	{
		if (env->car->next)
			env->car = env->car->next;
		else
			break ;
		i++;
	}
	while (env->tri)
	{
		if (env->tri->next)
			env->tri = env->tri->next;
		else
			break ;
		i++;
	}
	while (env->pla)
	{
		if (env->pla->next)
			env->pla = env->pla->next;
		else
			break ;
		i++;
	}
	while (env->cyl)
	{
		if (env->cyl->next)
			env->cyl = env->cyl->next;
		else
			break ;
		i++;
	}
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

void		obj_sph(t_env *env, t_obj *obj)
{
	reset_obj(obj);
	obj->sph = env->sph;
	obj->color = obj->sph->color;
	obj->sph->next = NULL;
/*	else if (ft_strcmp("car", txt) == 0)
	{
		obj->car->next = NULL;
		obj->color = obj->car->color;
	}
	else if (ft_strcmp("cyl", txt) == 0)
	{
		obj->cyl->next = NULL;
		obj->color = obj->cyl->color;
	}
	else if (ft_strcmp("tri", txt) == 0)
	{
		obj->tri->next = NULL;
		obj->color = obj->tri->color;
	}
	else if (ft_strcmp("pla", txt) == 0)
	{
		obj->pla->next = NULL;
		obj->color = obj->pla->color;
	}*/
}

void		reset_obj(t_obj *obj)
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
