#include "miniRT.h"

t_ray		*init_ray()
{
	t_ray	*ray;

	if (!(ray = malloc(sizeof(t_ray))))
		return (NULL);
	ray->pos = v_init(0, 0, 0);
	ray->dir = v_init(0, 0, 0);
	ray->t = 0;
	ray->next = NULL;
	ray->prev = NULL;
	return (ray);
}

void		ft_ray(t_ray *ray, t_v3 ori, t_v3 dir, double t)
{
	ray->pos = ori;
	ray->dir = dir;
	ray->t = t;
	ray->next = NULL;
	ray->prev = NULL;
}
