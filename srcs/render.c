/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:11:21 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/05 16:43:34 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	render_all(t_env *env, int nb)
{
	
}

int			render(t_env *env, bool save)
{
	if (save)
	{
		render_all(env, 1);
		set_save(env, BMP_FILE);
	}
}
