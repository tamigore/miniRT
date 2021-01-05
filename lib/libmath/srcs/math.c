#include "libmath.h"

double		ft_pow(double x, int i)
{
	double	nb;

	if (x == 0)
		return 1;
	nb = 1;
	while (i-- > 0)
	{
		nb *= x;
	}
	return (nb);
}
