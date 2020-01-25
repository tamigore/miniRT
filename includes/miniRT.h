/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:30:18 by tamigore          #+#    #+#             */
/*   Updated: 2020/01/25 19:09:22 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINIRT_H_
# define _MINIRT_H_

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "mlx.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>

typedef struct		s_env
{
	struct s_cam	*cam;
	struct s_ray	*ray;
	struct s_lum	*lum;
	struct s_obj	*obj;
}					t_env;

#endif
