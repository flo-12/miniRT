
#include "miniRT.h"

void	print_color(t_color color)
{
	printf("[COLOR] r=%d | g=%d | b=%d\n", 
		color.r, color.g, color.b);
}

void	print_coord(t_coordinates coord)
{
	printf("[COORDINATES] x=%f | y=%f | z=%f\n", 
		coord.x, coord.y, coord.z);
}

void	print_nbr(float p)
{
	printf("[NBR] p=%f\n", p);
}

void	print_light(t_light light, int e)
{
	printf("\n****** PRINT_LIGHT ******\n");
	print_coord(*light.point);
	print_nbr(light.brightness);
	print_color(*light.color);
	printf("exit code = %d\n", e);
}

void	print_camera(t_camera cam, int e)
{
	printf("\n****** PRINT_CAMERA ******\n");
	print_coord(*cam.point);
	print_coord(*cam.v_norm);
	print_nbr(cam.fov);
	printf("exit code = %d\n", e);
}

void	print_ambient(t_ambient amb, int e)
{
	printf("\n****** PRINT_AMBIENT ******\n");
	print_nbr(amb.ratio);
	print_color(*amb.color);
	printf("exit code = %d\n", e);
}

void	print_objects(t_object *objs, int e)
{
	printf("\n****** PRINT_OBJECTS ******\n");
	if (!objs)
		printf("No object initialized\n");
	while (objs)
	{
		if (objs->identifier == SPHERE)
		{
			printf("Object Type: SPHERE\n");
			print_coord(*objs->u_obj.sphere.center);
			print_nbr(objs->u_obj.sphere.d);
			print_color(*objs->u_obj.sphere.color);
		}
		else if (objs->identifier == PLANE)
		{
			printf("Object Type: PLANE\n");
			print_coord(*objs->u_obj.plane.point);
			print_coord(*objs->u_obj.plane.v_norm);
			print_color(*objs->u_obj.plane.color);
		}
		else if (objs->identifier == CYLINDER)
		{
			printf("Object Type: CYLINDER\n");
			print_coord(*objs->u_obj.cylinder.center);
			print_coord(*objs->u_obj.cylinder.v_norm);
			print_nbr(objs->u_obj.cylinder.d);
			print_nbr(objs->u_obj.cylinder.h);
			print_color(*objs->u_obj.cylinder.color);
		}
		else
			printf("Wrong identifier (id=%d)\n", objs->identifier);
		objs = objs->next;
	}
	printf("exit code = %d\n", e);
}

void	print_parse(t_global *global, t_exit_code e)
{
	if (e)
		return ;
	if (global->light)
		print_light(*global->light, e);
	if (global->camera)	
		print_camera(*global->camera, e);
	if (global->ambient)	
		print_ambient(*global->ambient, e);
	if (global->objects)	
		print_objects(global->objects, e);
}

/*
int	main(int argc, char **argv)
{
	int			e;
	t_global	*global;

	(void)argc;
	global = malloc(sizeof(t_global));
	global->light = NULL;
	global->camera = NULL;
	global->ambient = NULL;
	global->objects = NULL;

	e = parse(argv[1], global);
	if (e != SUCCESS)
		printf("ERROR -> exit-code %d\n", e);
	else
	{
		print_light(*global->light, e);
		print_camera(*global->camera, e);
		print_ambient(*global->ambient, e);
		print_objects(global->objects, e);
	}
	
	return (0);
}
*/
