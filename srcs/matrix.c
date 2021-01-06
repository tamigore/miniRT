#include "miniRT.h"

double	**lookAt(double **cam2world, t_v3 dir, t_v3 pos)
{
	t_v3	X;
	t_v3	Y;
	t_v3	Z;
//	double	**mat;

	Z = v_norm(v_sub(dir, pos));
	if (v_comp(X = v_cross(v_init(0, 1, 0), Z), v_init(0, 0, 0)))
		X = v_cross(v_init(1, 0, 0), Z);
	Y = v_cross(Z, X);
	matrix_row(X.x, X.y, X.z, pos.x, cam2world[0]);
	matrix_row(Y.x, Y.y, Y.z, pos.y, cam2world[1]);
	matrix_row(Z.x, Z.z, Z.z, pos.z, cam2world[2]);
	matrix_row(0, 0, 0, 1, cam2world[3]);
//	if (!(mat = matrix44_init()))
//		return (NULL);
//	matrix_row(1, 0, 0, -pos.x, mat[0]);
//	matrix_row(0, 1, 0, -pos.y, mat[1]);
//	matrix_row(0, 0, 1, -pos.z, mat[2]);
//	mat[3][3] = 1;
//	cam2world = mat4Xmat4(cam2world, mat);
//	if (!(inv_matrix(cam2world, mat)))
//		return (NULL);
	return (cam2world);
}
