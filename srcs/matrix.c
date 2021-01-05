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

double		**matrix44_init()
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

void		matrix_row(double a, double b, double c, double d, double *M)
{
	M[0] = a;
	M[1] = b;
	M[2] = c;
	M[3] = d;
}

double		**mat4Xmat4(double **m, double **z)
{
	double	**mat;
	int		i;
	int		j;
	int		k;

	if (!(mat = matrix44_init()))
		return (NULL);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				mat[i][j]=m[i][k]*z[k][j]+mat[i][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (mat);
}

t_v3		vec3Xmat4(t_v3 vec, double **M)
{
	t_v3	res;

	res.x = M[0][0] * vec.x + M[0][1] * vec.y + M[0][2] * vec.z + M[0][3];
	res.y = M[1][0] * vec.x + M[1][1] * vec.y + M[1][2] * vec.z + M[1][3];
	res.z = M[2][0] * vec.x + M[2][1] * vec.y + M[2][2] * vec.z + M[2][3];
	return (res);
}

int			inv_matrix(double **m, double **invert)
{
	double	inv[4][4];
	double	det;
	int		i;
	int		j;

	inv[0][0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] -
				m[2][1] * m[1][3] * m[3][3] + m[2][2] * m[1][3] * m[3][2] +
				m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];

	inv[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] +
				m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] -
				m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];

	inv[2][0] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] -
				m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] +
				m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];

	inv[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] +
				m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] -
				m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

	inv[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] +
				m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] -
				m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];

	inv[1][1] = m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] -
				m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] +
				m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];

	inv[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] +
				m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] -
				m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];

	inv[3][1] = m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] -
				m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] +
				m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];

	inv[0][2] = m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] -
				m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] +
				m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];

	inv[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] +
				m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] -
				m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];

	inv[2][2] = m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] -
				m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] +
				m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];

	inv[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] +
				m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] -
				m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];

	 inv[0][3] = -m[0][1] * m[1][2] * m[2][1] + m[0][1] * m[1][3] * m[2][2] +
				m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] -
				m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];

	inv[1][3] = m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] -
				m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + 
				m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];

	inv[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] +
				m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] -
				m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];

	inv[3][3] = m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] -
				m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] +
				m[2][0] * m[0][1] * m[1][2] -  m[2][0] * m[0][2] * m[2][1];

	det = m[0][0] * inv[0][0] + m[0][1] * inv[1][0] + m[0][2] * inv[2][0] + m[0][3] * inv[3][0];
	if (det == 0)
		return (0);
	det = 1.0 / det;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			invert[i][j] = inv[i][j] * det;
			j++;
		}
		i++;
	}
	return (1);
}
