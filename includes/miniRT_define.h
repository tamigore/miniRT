/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:41:50 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 19:04:10 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H

# define BMP_FILE "miniRT.bmp"
# define FILE_PERM 0644
# define FAIL -1
# define WIN 1
# define END 0
# define TITLE "miniRT"
# define PIXEL_LEN 4
# define EPSILON 0.0001
# define OBJ_MOVE 1
# define LUMEN 100

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
# define MLGT_ID "L"
# define MCAM_ID "C"
# define TRI_ID "tr"
# define CYL_ID "cy"
# define SPH_ID "sp"
# define PLA_ID "pl"

/*
**	errors
*/

# define AMB_DUP "Invalid scene: Ambient light must be declared once.\n"
# define MB_FMT "Invalid scene: Ambient light badly formatted.\n"
# define CAM_FMT "Invalid scene: Camera badly formatted.\n"
# define COLOR_FMT "Invalid scene: Color badly formatted.\n"
# define COORD_FMT "Invalid scene: Coordinates badly formatted.\n"
# define CYL_FMT "Invalid scene: Cylinder badly formatted.\n"
# define FD_ERR "Invalid file descriptor: Open failed.\n"
# define DOUBLE_FMT "Invalid scene: doubleing-point number badly formatted.\n"
# define ID_ERR "Invalid scene: Unknown identifier.\n"
# define LIGHT_FMT "Invalid scene: Light badly formatted.\n"
# define NO_AMB "No ambient light declared. Rendering stopped.\n"
# define NO_CAM "No camera declared. Rendering stopped.\n"
# define NO_LIGHT "No light declared. Rendering stopped.\n"
# define NO_OBJ "No object declared. Rendering stopped.\n"
# define NUM_FMT "Invalid scene: Number badly formatted.\n"
# define PLANE_FMT "Invalid scene: Plane badly formatted.\n"
# define RES_DUP "Invalid scene: Resolution must be declared once.\n"
# define RES_LOW "Resolution too low: minimum is 300x300. Rendering stopped.\n"
# define SCENE_FMT "Invalid scene: Scene badly formatted.\n"
# define SPHERE_FMT "Invalid scene: Sphere badly formatted.\n"
# define ERRNO_TO_STR "Malloc error.\n"

/*
**	mlx
*/

// # define KEYPRESSMASK 1
// # define STRUCTURENOTIFYMASK 131072

# define KEYPRESS 2
# define KEYRELEASE 3
# define BUTTONPRESS 4
# define BUTTONRELEASE 5
# define MOTIONNOTIFY 6
# define ENTERNOTIFY 7
# define LEAVENOTIFY 8
# define FOCUSIN 9
# define FOCUSOUT 10
# define KEYMAPNOTIFY 11
# define EXPOSE 12
# define GRAPHICSEXPOSE 13
# define NOEXPOSE 14
# define VISIBILITYNOTIFY 15
# define CREATENOTIFY 16
# define DESTROYNOTIFY 17
# define UNMAPNOTIFY 18
# define MAPNOTIFY 19
# define MAPREQUEST 20
# define REPARENTNOTIFY 21
# define CONFIGURENOTIFY 22
# define CONFIGUREREQUEST 23
# define GRAVITYNOTIFY 24

/*
** Mouse button keycodes
*/

# define BUT1_KEY 1
# define BUT2_KEY 2
# define BUT3_KEY 3
# define SCROLLUP_KEY 4
# define SCROLLDOWN_KEY 5
# define SCROLLLEFT_KEY 6
# define SCROLLRIGHT_KEY 7

/*
** Keyboard keys
*/

/*
** Letters keys
*/

# define A_KEY 97
# define B_KEY 11
# define C_KEY 8
# define D_KEY 100
# define E_KEY 14
# define F_KEY 102
# define G_KEY 5
# define H_KEY 4
# define I_KEY 34
# define J_KEY 38
# define K_KEY 40
# define L_KEY 37
# define M_KEY 46
# define N_KEY 45
# define O_KEY 31
# define P_KEY 35
# define Q_KEY 12
# define R_KEY 114
# define S_KEY 115
# define T_KEY 17
# define U_KEY 32
# define V_KEY 9
# define W_KEY 119
# define X_KEY 7
# define Y_KEY 16
# define Z_KEY 6

/*
** Numbers (not numeric keypad ones)
*/

# define K1_KEY 18
# define K2_KEY 19
# define K3_KEY 20
# define K4_KEY 21
# define K5_KEY 23
# define K6_KEY 22
# define K7_KEY 26
# define K8_KEY 28
# define K9_KEY 25
# define K0_KEY 29

/*
** Special characters
** SP_KEY is the space ( ) key
** BQ_KEY is the back quote (`) and tilde (~) key
** MN_KEY is the minus (-) and underscore (_) key
** PL_KEY is the plus (+) and equal (=) key
** SBO_KEY is the square bracket opening ([) and brace opening ({) key
** SBC_KEY is the square bracket closing (]) and brace closing (}) key
** BSL_KEY is the backslash (\) and pipe (|) key
** SC_KEY is the semicolon (;) and colon (:) key
** SQ_KEY is the simple quote (') and double quote (") key
** CM_KEY is the comma (,) and angle bracket opening (<) key
** PT_KEY is the point (.) and angle bracket closing (>) key
** SL_KEY is the slash (/) and question mark (?) key
*/

# ifdef MACOS
#  define SP_KEY 49
# else
#  define SP_KEY 32
# endif
# define BQ_KEY 50
# define MN_KEY 27
# define PL_KEY 24
# define SBO_KEY 33
# define SBC_KEY 30
# define BSL_KEY 42
# define SC_KEY 41
# define SQ_KEY 39
# define CM_KEY 43
# define PT_KEY 47
# define SL_KEY 44

/*
** Arrow keys
*/

# define UP_KEY 65362
# define DOWN_KEY 65364
# define RIGHT_KEY 65363
# define LEFT_KEY 65361

/*
** Special keys
** CL_KEY is the caps lock key
** LSFT_KEY and RLFT_KEY are the left shift and right shift keys
** LCTRL_KEY and RCTRL_KEY are the left control and right control keys
** LOPT_KEY and ROPT_KEY are the left option and right option keys
** LCMD_KEY and RCMD_KEY are the left command and right command keys
** LDEL_KEY and RDEL_KEY are the left delete and right delete keys
** RTN_KEY is the return key
** EJ_KEY is the eject key and doesn't react
** PUP_KEY and PDOWN_KEY are the page up and page down keys
** CLR_KEY is the clear key
*/

# ifdef MACOS
#  define ESC_KEY 53
# else
#  define ESC_KEY 65307
# endif
# define TAB_KEY 48
# define CL_KEY 272
# define LSFT_KEY 65505
# define LCTRL_KEY 256
# define LOPT_KEY 261
# define LCMD_KEY 259
# define LDEL_KEY 51
# define RTN_KEY 36
# define RSFT_KEY 258
# define RCTRL_KEY 269
# define ROPT_KEY 262
# define RCMD_KEY 260
# define EJ_KEY
# define FN_KEY 279
# define RDEL_KEY 117
# define HOME_KEY 115
# define END_KEY 119
# define PUP_KEY 116
# define PDOWN_KEY 121
# define CLR_KEY 71

/*
** Numeric keyboard keys, preceded by NK
** NKEQ_KEY is the equal (=) key
** NKSL_KEY is the slash (/) key
** NKWC_KEY is the wildcard (*) key
** NKMN_KEY is the minus (-) key
** NKPL_KEY is the plus (+) key
** NKPT_KEY is the point (.) key
** NKNTR_KEY is the enter key
*/

# define NK1_KEY 83
# define NK2_KEY 84
# define NK3_KEY 85
# define NK4_KEY 86
# define NK5_KEY 87
# define NK6_KEY 88
# define NK7_KEY 89
# define NK8_KEY 91
# define NK9_KEY 92
# define NK0_KEY 82
# define NKEQ_KEY 81
# define NKSL_KEY 75
# define NKWC_KEY 67
# define NKMN_KEY 78
# define NKPL_KEY 69
# define NKPT_KEY 65
# define NKNTR_KEY 76

#endif
