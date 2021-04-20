/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:04:48 by tamigore          #+#    #+#             */
/*   Updated: 2021/04/20 11:56:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** array of error identifiers associated to error messages
*/

static t_err	g_errors[] =
{
	{ AMB_DUP, "Invalid scene: Ambient light must be declared once." },
	{ AMB_FMT, "Invalid scene: Ambient light badly formatted." },
	{ CAM_FMT, "Invalid scene: Camera badly formatted." },
	{ COLOR_FMT, "Invalid scene: Color badly formatted." },
	{ COORD_FMT, "Invalid scene: Coordinates badly formatted." },
	{ CYL_FMT, "Invalid scene: Cylinder badly formatted." },
	{ FLOAT_FMT, "Invalid scene: Floating-point number badly formatted." },
	{ FD_ERR, "Invalid scene file: Use the '.rt' extension." },
	{ ID_ERR, "Invalid scene: Unknown identifier." },
	{ LIGHT_FMT, "Invalid scene: Light badly formatted." },
	{ NO_AMB, "No ambient light declared. Rendering stopped." },
	{ NO_CAM, "No camera declared. Rendering stopped." },
	{ NO_LIGHT, "No light declared. Rendering stopped." },
	{ NO_OBJ, "No object declared. Rendering stopped." },
	{ NO_RES, "No resolution declared. Rendering stopped." },
	{ NUM_FMT, "Invalid scene: Number badly formatted." },
	{ OPT_ERR, "Invalid option: Try '--save'." },
	{ PLANE_FMT, "Invalid scene: Plane badly formatted." },
	{ RES_DUP, "Invalid scene: Resolution must be declared once." },
	{ RES_LOW, "Resolution too low: minimum is 300x300. Rendering stopped." },
	{ SCENE_FMT, "Invalid scene: Scene badly formatted." },
	{ SPHERE_FMT, "Invalid scene: Sphere badly formatted." },
	{ SQUARE_FMT, "Invalid scene: Square badly formatted." },
};

/*
** This function retrieves the appropriate error message using given error id
*/

static char		*get_error_msg(t_errid id)
{
	if (id != ERRNO_TO_STR)
		return (g_errors[id].msg);
	return ((char *)strerror(FAIL));
}

static void		print_err(t_errid id)
{
	char	*msg;

	msg = get_error_msg(id);
	write(STDERR_FILENO, "Error\n", ft_strlen("Error\n"));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

int				exit_sucess(t_env *env)
{
	free_env(env);
	ft_putstr("EXIT\n");
	exit(END);
	return (0);
}

void			exit_error(t_env *env, t_errid id)
{
	free_env(env);
	print_err(id);
}
