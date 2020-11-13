#include "miniRT.h"

void	print_env(t_env *env)
{
	if (env->res)
		printf("res :%d.x/%d.y\n", env->res->x, env->res->y);
	if (env->amb)
		printf("amb :%d.R/%d.G/%d.B // %.2f.l\n", env->amb->R, env->amb->G,
		env->amb->B, env->amb->l);
	print_cam(env->cam);
	print_lum(env->lum);
	print_cyl(env->cyl);
	print_car(env->car);
	print_tri(env->tri);
	print_pla(env->pla);
	print_sph(env->sph);
	if (env->ray)
		printf("ray :%.2f.x/%.2f.y/%.2f.z//%.2f.vx/%.2f.vy/%.2f.vz)//t=%.2f\n",
		env->ray->ori.x, env->ray->ori.y, env->ray->ori.z, env->ray->dir.x,
		env->ray->dir.y, env->ray->dir.z, env->ray->t);
}

void	print_cam(t_cam *cam)
{
	if (cam)
	{
		while (cam)
		{
			printf("cam :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz //%d.fov\n", cam->ori.x, cam->ori.y,
			cam->ori.z, cam->dir.x, cam->dir.y, cam->dir.z, cam->fov);
			if (cam->next)
				cam = cam->next;
			else
				break;
		}
	}
	else
		printf("cam :NULL\n");
}

void	print_lum(t_lum *lum)
{
	if (lum)
	{
		while (lum)
		{
			printf("lum :%.2f.x/%.2f.y/%.2f.z // %f.l // %d.R/%d.G/%d.B\n", lum->ori.x, lum->ori.y,
			lum->ori.z, lum->l, lum->R, lum->G, lum->B);
			if (lum->next)
				lum = lum->next;
			else
				break;
		}
	}
	else
		printf("lum :NULL\n");
}

void	print_cyl(t_cyl *cyl)
{
	if (cyl)
	{
		while (cyl)
		{
			printf("cyl :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %d.R/%d.G/%d.B // %.2f.h/%.2f.d\n", cyl->ori.x, cyl->ori.y,
			cyl->ori.z, cyl->dir.x, cyl->dir.y, cyl->dir.z, cyl->R, cyl->G, cyl->B, cyl->h, cyl->d);
			if (cyl->next)
				cyl = cyl->next;
			else
				break;
		}
	}
	else
		printf("cyl :NULL\n");
}

void	print_car(t_car *car)
{
	if (car)
	{
		while (car)
		{
			printf("car :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %d.R/%d.G/%d.B // %.2f.h\n", car->ori.x, car->ori.y,
			car->ori.z, car->dir.x, car->dir.y, car->dir.z, car->R, car->G, car->B, car->h);
			if (car->next)
				car = car->next;
			else
				break;
		}
	}
	else
		printf("car :NULL\n");
}

void	print_tri(t_tri *tri)
{
	if (tri)
	{
		while (tri)
		{
			printf("tri :%.2f.x1/%.2f.y1/%.2f.z1 // %.2f.x2/%.2f.y2/%.2f.z2 // %.2f.x3/%.2f.y3/%.2f.z3 // %d.R/%d.G/%d.B\n", tri->p1.x, tri->p1.y, tri->p1.z,
			tri->p2.x, tri->p2.y, tri->p2.z, tri->p3.z, tri->p3.y, tri->p3.z, tri->R, tri->G, tri->B);
			if (tri->next)
				tri = tri->next;
			else
				break;
		}
	}
	else
		printf("tri :NULL\n");
}

void	print_pla(t_pla *pla)
{
	if (pla)
	{
		while (pla)
		{
			printf("pla :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %d.R/%d.G/%d.B\n", pla->ori.x, pla->ori.y,
			pla->ori.z, pla->dir.x, pla->dir.y, pla->dir.z, pla->R, pla->G, pla->B);
			if (pla->next)
				pla = pla->next;
			else
				break;
		}
	}
	else
		printf("pla :NULL\n");
}

void	print_sph(t_sph *sph)
{
	if (sph)
	{
		while (sph)
		{
			printf("sph :%.2f.x/%.2f.y/%.2f.z // %.2f.d // %d.R/%d.G/%d.B\n", sph->ori.x, sph->ori.y,
			sph->ori.z, sph->d, sph->R, sph->G, sph->B);
			if (sph->next)
				sph = sph->next;
			else
				break;
		}
	}
	else
		printf("sph :NULL\n");
}

void	print_ray(t_ray *ray)
{
	if (ray)
		printf("ray :%.2f.x/%.2f.y/%.2f.z//%.2f.vx/%.2f.vy/%.2f.vz)//t=%.2f\n",
		ray->ori.x, ray->ori.y, ray->ori.z, ray->dir.x,
		ray->dir.y, ray->dir.z, ray->t);
}

void	print_obj(t_obj *obj)
{
	if (obj)
	{
		printf("obj :%d.nb/%.2f.dist/%d.color\n", obj->nb, obj->dist, obj->color);
		print_cyl(obj->cyl);
		print_car(obj->car);
		print_tri(obj->tri);
		print_pla(obj->pla);
		print_sph(obj->sph);
	}
	else
		printf("obj :NULL\n");
}

