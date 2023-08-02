
#include "miniRT.h"

void	print_color(t_color color, int e)
{
	printf("[COLOR] r=%d | g=%d | b=%d | with exit code %d\n", 
		color.r, color.g, color.b, e);
}

void	print_coord(t_coordinates coord, int e)
{
	printf("[COORDINATES] x=%f | y=%f | z=%f | with exit code %d\n", 
		coord.x, coord.y, coord.z, e);
}

void	print_nbr(float p, int e)
{
	printf("[NBR] p=%f with exit code %d\n", p, e);
}

int	main(void)
{
	int	e;
	t_global	*global;

	global = malloc(sizeof(t_global));
	global->light = malloc(sizeof(t_light));
	global->light->point = malloc(sizeof(t_coordinates));
	global->light->color = malloc(sizeof(t_color));

	e = store_color(ft_strdup("10,0,256"), global->light->color);
	print_color(*global->light->color, e);
	e = store_coordinates(ft_strdup("-40.a0,50.0,0.0"), global->light->point);
	print_coord(*global->light->point, e);
	e = store_nbr_float(ft_strdup("0.6"), -1, 1, &global->light->brightness);
	print_nbr(global->light->brightness, e);

	return (0);
}