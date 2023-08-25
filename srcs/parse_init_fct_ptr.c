/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_fct_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:26:36 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/25 12:26:37 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_fct_ptr_sphere(t_object *obj)
{
	obj->fct_free = &free_sphere;
	obj->fct_intersect = &intersect_sphere;
	obj->fct_color = &color_sphere;
	obj->fct_surface_norm = &surface_norm_sphere;
	obj->fct_in_object = &fct_inside_sphere;
}

void	init_fct_ptr_plane(t_object *obj)
{
	obj->fct_free = &free_plane;
	obj->fct_intersect = &intersect_plane;
	obj->fct_color = &color_plane;
	obj->fct_surface_norm = &surface_norm_plane;
	obj->fct_in_object = &fct_inside_plane;
}

void	init_fct_ptr_cylinder(t_object *obj)
{
	obj->fct_free = &free_cylinder;
	obj->fct_intersect = &intersect_cylinder;
	obj->fct_color = &color_cylinder;
	obj->fct_surface_norm = &surface_norm_cylinder;
	obj->fct_in_object = &fct_inside_cylinder;
}

void	init_fct_ptr_cone(t_object *obj)
{
	obj->fct_free = &free_cone;
	obj->fct_intersect = &intersect_cone;
	obj->fct_color = &color_cone;
	obj->fct_surface_norm = &surface_norm_cone;
	obj->fct_in_object = &fct_inside_cone;
}

/* init_fct_ptr:
*	Initializes the function pointers.
*
*	Return: -
*/
void	init_fct_ptr(int id, t_object *obj)
{
	if (id == SPHERE)
		init_fct_ptr_sphere(obj);
	else if (id == PLANE)
		init_fct_ptr_plane(obj);
	else if (id == CYLINDER)
		init_fct_ptr_cylinder(obj);
	else if (id == CONE)
		init_fct_ptr_cone(obj);
}
