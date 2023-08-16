/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:24:03 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/04 13:24:05 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* intersect_sphere:
*	Calculates the intersection points between a ray
*	and a sphere. If there is only one intersection,
*	the two intersection points are equal. The result
*	of the equation is stored in the argument hit.
*	
*	Given is a sphere with the equation:
*		(x - x_C)^2 + (y - y_C)^2 + (z - z_C)^2 = r^2
*	and a center C(x_C, y_C, z_C) and a radius r.
*	x, y, z in the equation are substituded by the 
*	ray with x = x_O + t*x_v with the origin
*	O(x_O, y_O, z_O) and the normed direction vector
*	V(x_v, y_v, z_v).
*	The equation is solved for t with t beeing the
*	two points of intersection - if inserted in the 
*	vector function of the ray.
*	If t is negative, the hit point lies behind
*	the origin. If t is 0, the hit point and the
*	origin overlap. If t is positiv, the hit point
*	lies in front of the origin (concerning the
*	direction vector).
*	Hit points behind the origin are not valid, b/c
*	they are behind the viewers perspective.
*
*	Return: TRUE if a valid intersection is found and
*		FALSE otherwise.
*/
bool	intersect_sphere(t_sphere sphere, t_vector ray, t_hit *hit)
{
	float	abc[3];
	float	t[2];

	abc[0] = powf(ray.v_norm.x, 2) + powf(ray.v_norm.y, 2) 
		+ powf(ray.v_norm.z, 2);
	abc[1] = 2 * vec3_dot(ray.v_norm, vec3_sub(ray.origin, *sphere.center));
	abc[2] = powf((ray.origin.x - sphere.center->x), 2) 
		+ powf((ray.origin.y - sphere.center->y), 2) 
		+ powf((ray.origin.z - sphere.center->z), 2) 
		- powf((sphere.d / 2), 2);
	t[0] = (-abc[1] + sqrtf(powf(abc[1], 2) - 4 * abc[0] * abc[2])) 
		/ (2 * abc[0]);
	t[1] = (-abc[1] - sqrtf(powf(abc[1], 2) - 4 * abc[0] * abc[2])) 
		/ (2 * abc[0]);
	if ((t[0] < THRESH_FLOAT && t[1] < THRESH_FLOAT) 
		|| isnan(t[0]) || isnan(t[1]))
		return (false);
	else if (t[0] < THRESH_FLOAT)
		t[0] = t[1];
	else if (t[1] < THRESH_FLOAT)
		t[1] = t[0];
	hit->p1 = vec3_get_pt(ray, t[0]);
	hit->p2 = vec3_get_pt(ray, t[1]);
	return (true);
}

/* intersect_plane:
*	Calculates the intersection point between a ray
*	and a plane. The result of the equation is
*	stored in the argument hit (with hit.p1 = hit.p2).
*
*	Special cases:
*		- the origin of the ray lies on the plane (v_norm
*			orthogonal): no intersection point.
*		- the plane lies behind the origin of the ray
*			(in terms of direction of the ray): it's
*			not considered as a valid intersection
*			and hit won't be changed.
*
*	Return: TRUE if a valid intersection is found and
*		FALSE otherwise.
*/
bool	intersect_plane(t_plane plane, t_vector ray, t_hit *hit)
{
	float			numer;
	float			denom;
	float			d;
	t_coordinates	tmp;

	tmp.x = plane.point->x - ray.origin.x;
	tmp.y = plane.point->y - ray.origin.y;
	tmp.z = plane.point->z - ray.origin.z;
	numer = vec3_dot(tmp, *plane.v_norm);
	denom = vec3_dot(ray.v_norm, *plane.v_norm);
	if (equal(denom, 0))
		return (false);
	d = numer / denom;
	if (!vec3_pt_on_line(ray, vec3_get_pt(ray, d)))
		return (false);
	hit->p1 = vec3_get_pt(ray, d);
	hit->p2 = hit->p1;
	return (true);
}

/* intersect_tube:
*
*/
int	intersect_tube(t_cylinder cyl, t_vector ray, t_hit *hit)
{
	float			abc[3];
	float			d;
	float			t[2];
	t_coordinates	v;
	int				nbr_inter;

	nbr_inter = 0;
	abc[0] = vec3_dot(vec3_cross(ray.v_norm, *cyl.v_norm), 
			vec3_cross(ray.v_norm, *cyl.v_norm));
	v = vec3_cross(vec3_sub(ray.origin, *cyl.center), *cyl.v_norm);
	abc[1] = 2 * vec3_dot(vec3_cross(ray.v_norm, *cyl.v_norm), v);
	abc[2] = vec3_dot(v, v) - powf(cyl.d / 2, 2);
	d = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (d < THRESH_FLOAT || abc[0] < THRESH_FLOAT)
		return (nbr_inter);
	d = sqrtf(d);
	t[0] = (-abc[1] + d) / (2 * abc[0]);
	t[1] = (-abc[1] - d) / (2 * abc[0]);
	nbr_inter = tube_check_valid_points(ray, &t, cyl);
	hit->p1 = vec3_get_pt(ray, t[0]);
	hit->p2 = vec3_get_pt(ray, t[1]);
	return (nbr_inter);
}

/* intersect_cylinder:
*	Calculates the intersection point between a ray
*	and a cylinder. The result of the equation is
*	stored in the argument hit (with hit.p1 = hit.p2).
*
*	Special cases:
*
*	Return: TRUE if a valid intersection is found and
*		FALSE otherwise.
*/
bool	intersect_cylinder(t_cylinder cyl, t_vector ray, t_hit *hit)
{
	int		nbr_inter;
	t_hit	hit_tmp;

	nbr_inter = intersect_tube(cyl, ray, hit);
	if (nbr_inter == 2)
		return (true);

	if (intersect_plane((t_plane){cyl.center, cyl.v_norm, cyl.color}, ray, &hit_tmp) 
		&& vec3_dist_pts(hit_tmp.p1, *cyl.center) <= cyl.d / 2)
	{
		nbr_inter++;
		if (nbr_inter == 2)
		{
			hit->p1 = hit_tmp.p1;
			return (true);
		}
		else
			hit->p1 = hit_tmp.p1;
	}

	t_coordinates	p = vec3_add(vec3_multiply_const(*cyl.v_norm, cyl.h), *cyl.center);
	if (intersect_plane((t_plane){&p, cyl.v_norm, cyl.color}, ray, &hit_tmp) 
		&& vec3_dist_pts(hit_tmp.p1, p) <= cyl.d / 2)
	{
		nbr_inter++;
		if (nbr_inter == 1)
		{
			hit->p1 = hit_tmp.p1;
			hit->p2 = hit_tmp.p1;
		}
		else if (nbr_inter == 2)
			hit->p2 = hit_tmp.p1;
	}

	if (nbr_inter > 0)
		return (true);
	else
		return (false);
}

/* intersect:
*	Calculates the intersection points (2 points)
*	between an object and a ray and stores the result
*	in the argument hit.
*	Differentiates between different types of
*	objects.
*
*	Return: TRUE if there is an intersection point
*		between the ray and the object and FALSE
*		otherwise.
*/
bool	render_intersect(t_object obj, t_vector ray, t_hit *hit)
{
	if (obj.identifier == SPHERE)
		return (intersect_sphere(obj.u_obj.sphere, ray, hit));
	else if (obj.identifier == PLANE)
		return (intersect_plane(obj.u_obj.plane, ray, hit));
	else if (obj.identifier == CYLINDER)
		return (intersect_cylinder(obj.u_obj.cylinder, ray, hit));
	else
		return (false);
}
