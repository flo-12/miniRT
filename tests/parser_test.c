
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

	/* split = split_line(strdup("L -40.0,50.0,0.0 0.6 10,0,255"));
	e = parse_light(split, &global->light);
	print_light(*global->light, e);

	split = split_line(ft_strdup("C -50.0,0,20 0,0,1 70"));
	e = parse_camera(split, &global->camera);
	print_camera(*global->camera, e);

	split = split_line(ft_strdup("A 0.2 255,255,255"));
	e = parse_ambient_ligthing(split, &global->ambient);
	print_ambient(*global->ambient, e);

	split = split_line(ft_strdup("sp 0.0,0.0,20.6 12.6 10,0,255"));
	e = parse_object(split, &global->objects, SPHERE);
	if (e != SUCCESS)
		printf("error objects (exit-code %d)\n", e);
	split = split_line(ft_strdup("pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225"));
	e = parse_object(split, &global->objects, PLANE);
	if (e != SUCCESS)
		printf("error objects (exit-code %d)\n", e);
	split = split_line(ft_strdup("cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255"));
	e = parse_object(split, &global->objects, CYLINDER);
	if (e != SUCCESS)
		printf("error objects (exit-code %d)\n", e);
	print_objects(global->objects, e); */
	
	return (0);
}