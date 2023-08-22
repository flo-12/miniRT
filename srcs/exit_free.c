/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:53:57 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/18 12:36:25 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* free_ambient_camera_light:
*	Frees all heap allocated memory in the structs
*	t_ambient, t_camera and t_light.
*/
void	free_ambient_camera_light(t_ambient *ambient, 
	t_camera *camera, t_light *light)
{
	t_light	*light_tmp;

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
	while (light)
	{
		free_if((void *)light->point);
		free_if((void *)light->color);
		light_tmp = light;
		light = light->next;
		free(light_tmp);
	}
}

/* exit_free:
*	Frees all heap allocated memory, exits mlx correct
*	and prints the corresponding exit code.
*/
t_exit_code	exit_free(t_global *global, t_exit_code e)
{
	free_ambient_camera_light(global->ambient, global->camera, global->light);
	while (global->objects)
		global->objects = (*global->objects->fct_free)(global->objects);
	free_mlx(global);
	free_if(global);
	print_exit(e);
	return (e);
}
