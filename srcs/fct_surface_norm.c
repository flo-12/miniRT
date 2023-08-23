/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_surface_norm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:56:08 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/23 14:56:11 by fbecht           ###   ########.fr       */
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

/* get_norm_cyl:
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
	t_cone			cone = obj.u_obj.cone;
	t_coordinates	ip;
	t_coordinates	ax_proj;
	t_coordinates	ax_perp;
	t_coordinates	t;

	ip = vec3_sub(shadow.origin, *cone.vertex);
	ax_proj = vec3_add(*cone.vertex, vec3_multiply_const(*cone.v_norm, 
				(vec3_dot(ip, *cone.v_norm) / 
					vec3_dot(*cone.v_norm, *cone.v_norm))));
	ax_perp = vec3_sub(shadow.origin, ax_proj);
	t = vec3_cross(ip, ax_perp);
	

	t_coordinates 	p = vec3_get_dir(*cone.vertex, shadow.origin);
	
	t = vec3_cross(t, ip);
	t_coordinates	r2 = vec3_norm(vec3_cross(*cone.v_norm, p));
	return (r2);

}
