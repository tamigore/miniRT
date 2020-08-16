/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgeo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:31:48 by tamigore          #+#    #+#             */
/*   Updated: 2020/08/15 16:53:55 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGEO_H
# define LIBGEO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef struct	s_v3
{
	double	x;
	double	y;
	double	z;
}		t_v3;

//RAD.C

double		rad(int deg);

//VECTOR.C

t_v3	v_init(double x, double y, double z);

#endif
