/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_in_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:28:34 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/25 10:28:36 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	fct_inside_sphere(t_object obj, t_coordinates p)
{
	t_sphere	sphere;

	sphere = obj.u_obj.sphere;
	if (vec3_dist_pts(p, *sphere.center) < sphere.d / 2)
			return (true);
	return (false);
}

bool	fct_inside_plane(t_object obj, t_coordinates p)
{
	(void)obj;
	(void)p;

	return (false);
}

bool	fct_inside_cylinder(t_object obj, t_coordinates p)
{
	/* t_cylinder	cyl;

	cyl = obj.u_obj.cylinder; */
	// ...
	(void)obj;
	(void)p;

	return (false);
}

bool	fct_inside_cone(t_object obj, t_coordinates p)
{
	(void)obj;
	(void)p;

	return (false);
}
