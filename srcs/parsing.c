/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:36:40 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/05 19:16:30 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** This function calls the appropriate function to parse a line
*/
static void	fill_env_sceen(t_env *env)
{
	if (!ft_strncmp(SPH_ID, env->sceen, ID_OBJ_LEN))
		get_sphere(env);
	else if (!ft_strncmp(PLA_ID, env->sceen, ID_OBJ_LEN))
		get_plane(env);
	else if (!ft_strncmp(CYL_ID, env->sceen, ID_OBJ_LEN))
		get_cylinder(env);
	else if (!ft_strncmp(TRI_ID, env->sceen, ID_OBJ_LEN))
		get_triangle(env);
	else if (!ft_strncmp(LGT_ID, env->sceen, ID_LEN)
		|| !ft_strncmp(MLGT_ID, env->sceen, ID_LEN))
		get_light(env);
	else if (!ft_strncmp(CAM_ID, env->sceen, ID_LEN)
		|| !ft_strncmp(MCAM_ID, env->sceen, ID_LEN))
		get_camera(env);
	else if (!ft_strncmp(AMB_ID, env->sceen, ID_LEN))
		get_ambient(env);
	else if (!ft_strncmp(RES_ID, env->sceen, ID_LEN))
		get_resolution(env);
}

/*
** This function compar all scene ID
*/
static int	comp_all(char *txt)
{
	if (!ft_strncmp(SPH_ID, txt, ID_OBJ_LEN)
		|| !ft_strncmp(PLA_ID, txt, ID_OBJ_LEN)
		|| !ft_strncmp(CYL_ID, txt, ID_OBJ_LEN)
		|| !ft_strncmp(TRI_ID, txt, ID_OBJ_LEN)
		|| !ft_strncmp(LGT_ID, txt, ID_LEN)
		|| !ft_strncmp(CAM_ID, txt, ID_LEN)
		|| !ft_strncmp(AMB_ID, txt, ID_LEN)
		|| !ft_strncmp(RES_ID, txt, ID_LEN)
		|| !ft_strncmp(MLGT_ID, txt, ID_LEN)
		|| !ft_strncmp(MCAM_ID, txt, ID_LEN))
		return (1);
	return (0);
}

/*
** This fonction read all the scene and return it as a string
*/
static char	*read_sceen(t_env *env, char *file_path)
{
	char	*result;
	char	buffer[BUFFER_SIZE + 1];
	int		fd;
	int		bytes_read;

	result = NULL;
	fd = open(file_path, O_RDONLY);
	if (!fd)
		exit_error(env, FD_ERR);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		result = ft_strjoindelone(result, buffer);
		if (!result)
			exit_error(env, ERRNO_TO_STR);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	close(fd);
	return (result);
}

/*
** This fonction pars the scene to the structures and check for errors
**
**	extra statement to add comment to .rt
**	else if (*(env->sceen) == '#')
**	{
**		while (*env->sceen && *env->sceen != '\n')
**			(env->sceen)++;
**	}
*/
void	pars_sceen(char *av, t_env *env)
{
	char	*head;

	env->sceen = read_sceen(env, av);
	if (!env->sceen)
		exit_error(env, ERRNO_TO_STR);
	head = env->sceen;
	while (*(env->sceen))
	{
		if (*(env->sceen) == '\n')
			(env->sceen)++;
		else if (comp_all(env->sceen))
			fill_env_sceen(env);
		else
		{
			env->sceen = head;
			exit_error(env, SCENE_FMT);
		}
	}
	if (env->nb_cam == 0 || env->nb_lgt == 0 || env->nb_obj == 0)
		exit_error(env, SCENE_FMT);
	env->sceen = NULL;
	free(head);
}
