/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:38:05 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/18 12:38:59 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_light(t_light *light, int e)
{
	printf("\n****** PRINT_LIGHT ******\n");
	if (!light)
		printf("No light initialized\n");
	while (light)
	{
		print_coord(*light->point);
		print_nbr(light->brightness);
		print_color(*light->color);
		light = light->next;
	}
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

void	print_parse(t_global *global, t_exit_code e)
{
	if (e)
		return ;
	if (global->light)
		print_light(global->light, e);
	if (global->camera)
		print_camera(*global->camera, e);
	if (global->ambient)
		print_ambient(*global->ambient, e);
	if (global->objects)
		print_objects(global->objects, e);
}
