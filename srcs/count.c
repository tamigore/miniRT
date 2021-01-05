#include "miniRT.h"

int			count_sph(t_sph *sph)
{
	int		i;

	i = 0;
	while (sph)
	{
		if (sph->next)
			sph = sph->next;
		else
			break ;
		i++;
	}
	return (0);
}

int			count_pla(t_pla *pla)
{
	int		i;

	i = 0;
	while (pla)
	{
		if (pla->next)
			pla = pla->next;
		else
			break ;
		i++;
	}
	return (i);
}

int			count_car(t_car *car)
{
	int		i;

	i = 0;
	while (car)
	{
		if (car->next)
			car = car->next;
		else
			break ;
		i++;
	}
	return (i);
}

int			count_cyl(t_cyl *cyl)
{
	int		i;

	i = 0;
	while (cyl)
	{
		if (cyl->next)
			cyl = cyl->next;
		else
			break ;
		i++;
	}
	return (i);
}

int			count_tri(t_tri *tri)
{
	int		i;

	i = 0;
	while (tri)
	{
		if (tri->next)
			tri = tri->next;
		else
			break ;
		i++;
	}
	return (i);
}

