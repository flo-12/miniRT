
#include "../includes/miniRT_define.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

void	tests_cylinder();
void	tests_sphere();
void	tests_plane();

t_coordinates	vector_normalize(t_coordinates v)
{
	t_coordinates	v_norm;
	float			magnitude;

	magnitude = sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
	v_norm.x = v.x / magnitude;
	v_norm.y = v.y / magnitude;
	v_norm.z = v.z / magnitude;
	return (v_norm);
}

int	main()
{
	printf("\n\n******* SPHERE *******\n");
	tests_sphere();

	printf("\n\n******* PLANE *******\n");
	tests_plane();

	printf("\n\n******* CYLINDER *******\n");
	tests_cylinder();

	printf("\n");
	return (0);
}
