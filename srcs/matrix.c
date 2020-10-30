#include "miniRT.h"

double	**lookAt(double **cam2world, t_v3 to, t_v3 from, t_v3 pos)
{
	t_v3	X;
	t_v3	Y;
	t_v3	Z;

	Z = v_norm(v_sub(from, to));
	X = v_cross(v_norm(v_init(0, 1, 0)), Z);
	Y = v_cross(Z, X);

	matrix_row(X.x, X.y, X.z, 0, cam2world[0]);
	matrix_row(Y.x, Y.y, Y.z, 0, cam2world[1]);
	matrix_row(Z.x, Z.y, Z.z, 0, cam2world[2]);
	matrix_row(pos.x, pos.y, pos.z, 1, cam2world[3]);
/*
	matrix_row(X.x, Y.x, Z.x, pos.x, cam2world[0]);
	matrix_row(X.y, Y.y, Z.y, pos.y, cam2world[1]);
	matrix_row(X.z, Y.z, Z.z, pos.z, cam2world[2]);
	matrix_row(0, 0, 0, 1, cam2world[3]);
*/
	return (cam2world);
}

double	**matrix44_init()
{
	double	**M;
	int		i;

	if (!(M = (double **)malloc(sizeof(double *) * 4)))
		return (NULL);
	i = 0;
	while (i < 4)
	{
		if (!(M[i++] = (double *)malloc(sizeof(double) * 4)))
			return (NULL);
	}
	i = 0;
	while (i < 4)
		matrix_row(0, 0, 0, 0, M[i++]);
	return (M);
}

void	matrix_row(double a, double b, double c, double d, double *M)
{
	M[0] = a;
	M[1] = b;
	M[2] = c;
	M[3] = d;
}

t_v3	vecXmat(t_v3 vec, double **M)
{
	t_v3	res;

	res.x = M[0][0] * vec.x + M[0][1] * vec.y + M[0][2] * vec.z + M[0][3];
	res.y = M[1][0] * vec.x + M[1][1] * vec.y + M[1][2] * vec.z + M[1][3];
	res.z = M[2][0] * vec.x + M[2][1] * vec.y + M[2][2] * vec.z + M[2][3];
	return (res);
}
