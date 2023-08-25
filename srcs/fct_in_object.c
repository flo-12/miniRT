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
	if (vec3_dist_pts(p, *sphere.center) <= sphere.d / 2)
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
	t_cylinder	cyl;
	float		h;
	float		r;

	cyl = obj.u_obj.cylinder;
	h = vec3_dot(vec3_sub(p, *cyl.center), *cyl.v_norm);
	r = sqrtf(powf(vec3_dist_pts(p, *cyl.center), 2) - powf(h, 2));
	if ((h <= cyl.h && h >= 0) && r <= cyl.d / 2)
		return (true);
	return (false);
}

bool	fct_inside_cone(t_object obj, t_coordinates p)
{
	t_cone		cone;
	float		h;
	float		hypo_c;
	float		hypo_p;

	cone = obj.u_obj.cone;
	h = vec3_dot(vec3_sub(p, *cone.vertex), *cone.v_norm);
	hypo_p = vec3_dist_pts(p, *cone.vertex);
	hypo_c = h / cosf(cone.angle / 2);
	if (h >= 0 && hypo_p <= hypo_c)
		return (true);
	return (false);
}
