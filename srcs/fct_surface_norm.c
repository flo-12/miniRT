/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_surface_norm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:56:08 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/25 09:26:35 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coordinates	surface_norm_plane(t_object obj, t_vector shadow)
{
	t_plane	plane;

	(void)shadow;
	plane = obj.u_obj.plane;
	return (*plane.v_norm);
}

t_coordinates	surface_norm_sphere(t_object obj, t_vector shadow)
{
	t_sphere	sphere;

	sphere = obj.u_obj.sphere;
	return (vec3_norm(vec3_sub(shadow.origin, *sphere.center)));
}

/* surface_norm_cylinder:
*	Calculates the normalized vector for the surface normal
*	of a cylinder by differentiating between the cap and the
*	tube of the cylinder with the following steps:
*		1) calculate the distance l (in direction of v_norm of
*			cylinder) of the hit point to the cylinder's
*			center
*		2) If cap: l is equal to 0 or the height of the cylinder
*		3) If tube: otherwise
*			- get the point p which is l away from the cylinder's
*				center in the direction of v_norm
*			- calculate the normalized vector of the surface
*				(identical to sphere with p being the center of
*				the sphere)
*
*	Return: the normalized surface vector.
*/
t_coordinates	surface_norm_cylinder(t_object obj, t_vector shadow)
{
	t_cylinder		cyl;
	t_coordinates	norm_obj;
	float			l;
	t_coordinates	p;

	cyl = obj.u_obj.cylinder;
	l = sqrtf(powf(vec3_dist_pts(shadow.origin, *cyl.center), 2) 
			- powf(cyl.d / 2, 2));
	if (equal(l, 0) || equal(l, cyl.h))
		norm_obj = *cyl.v_norm;
	else
	{
		p = vec3_add(*cyl.center, vec3_multiply_const(*cyl.v_norm, l));
		norm_obj = vec3_norm(vec3_sub(shadow.origin, p));
	}
	return (norm_obj);
}

t_coordinates	surface_norm_cone(t_object obj, t_vector shadow)
{
	t_coordinates	ip;
	t_coordinates	normal;
	t_cone			cone;

	cone = obj.u_obj.cone;
	ip = vec3_sub(*cone.vertex, shadow.origin);
	normal = vec3_cross(vec3_cross(*cone.v_norm, ip), ip);
	return (vec3_norm(normal));;
}
