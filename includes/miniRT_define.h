/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:41:50 by tamigore          #+#    #+#             */
/*   Updated: 2021/03/16 19:45:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINIRT_DEFINE_H_
# define _MINIRT_DEFINE_H_

# define BMP_FILE "miniRT.bmp"
# define FILE_PERM 0644
# define FAIL -1
# define WIN 1
# define END 0
# define TITLE "miniRT"
# define PIXEL_LEN 4
# define EPSILON 0.00001

/*
** color
*/

# define MAX_RGB 255
# define TRANS 3
# define RED 2
# define GREEN 1
# define BLUE 0

/*
** minirt ID
*/

# define ID_LEN 1
# define ID_OBJ_LEN 2
# define RES_ID "R"
# define AMB_ID "A"
# define LGT_ID "l"
# define CAM_ID "c"
# define SQR_ID "sq"
# define TRI_ID "tr"
# define CYL_ID "cy"
# define SPH_ID "sp"
# define PLA_ID "pl"

/*
** key code
*/

# define ESCAPE 65307
# define SPACE 32

/*
**	Xlib
*/

# define KEYPRESS 2
# define DESTROYNOTIFY 17
# define MAPNOTIFY 19

#endif
