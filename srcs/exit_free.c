#include "miniRT.h"

/* free_if:
*	Frees the pointer if it exists.
*/
void	free_if(void *ptr)
{
	if (ptr)
		free(ptr);
}

/* free_ambient_camera_light:
*	Frees all heap allocated memory in the structs
*	t_ambient, t_camera and t_light.
*/
void	free_ambient_camera_light(t_ambient *ambient, t_camera *camera, t_light *light)
{
	if (ambient)
	{
		free_if((void *)ambient->color);
		free(ambient);
	}
	if (camera)
	{
		free_if((void *)camera->point);
		free_if((void *)camera->v_norm);
		free(camera);
	}
	if (light)
	{
		free_if((void *)light->point);
		free_if((void *)light->color);
		free(light);
	}
}

/* free_objects:
*	Frees all the data in the linked-list t_object.
*/
void	free_objects(t_object *obj)
{
	t_object	*tmp;

	while (obj)
	{
		if (obj->identifier == SPHERE)
		{
			free_if((void *)obj->u_obj.sphere.center);
			free_if((void *)obj->u_obj.sphere.color);
		}
		else if (obj->identifier == PLANE)
		{
			free_if((void *)obj->u_obj.plane.point);
			free_if((void *)obj->u_obj.plane.v_norm);
			free_if((void *)obj->u_obj.plane.color);
		}
		if (obj->identifier == CYLINDER)
		{
			free_if((void *)obj->u_obj.cylinder.center);
			free_if((void *)obj->u_obj.cylinder.v_norm);
			free_if((void *)obj->u_obj.cylinder.color);
		}
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
}

/* print_exit:
*	Print the error message corresponding to the exit
*	codes in t_exit_code.
*/
void	print_exit(t_exit_code e)
{
	if (e)
	{
		printf("Error:");
		if (e == OPENFILE_ERROR)
			printf(MSG_OPENFILE_ERROR);
		else if (e == MLX_ERROR)
			printf(MSG_MLX_ERROR);
		else if (e == MALLOC_ERROR)
			printf(MSG_MALLOC_ERROR);
		if (e == INPUT_ERROR)
			printf(MSG_INPUT_ERROR);
		if (e == ARG_ERROR)
			printf(MSG_ARG_ERROR);
		if (e == INPUT_INCOMPLETE)
			printf(MSG_INPUT_INCOMPLETE);
		if (e == FILETYPE_ERROR)
			printf(MSG_FILETYPE_ERROR);
	}
}

/* exit_free:
*	Frees all heap allocated memory, exits mlx correct
*	and prints the corresponding exit code.
*/
t_exit_code	exit_free(t_global *global, t_exit_code e)
{
	free_ambient_camera_light(global->ambient, global->camera, global->light);
	free_objects(global->objects);
	free_mlx(global);

	free_if(global);
	print_exit(e);
	return (e);
}
