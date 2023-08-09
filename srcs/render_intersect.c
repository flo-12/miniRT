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



/* #include "../includes/miniRT_define.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h> */

/* equal:
*	Checks if two float numbers (nbr and comp) are equal,
*	whereas nbr lies in a range of comp+-THRESH_FLOAT.
*	This is done due to comparison / rounding problems
*	with floats.
*
*	Return: TRUE if the numbers are equal and FALSE
*		otherwise.
*/
/* bool	equal(float nbr, float comp)
{
	if (nbr > comp - THRESH_FLOAT && nbr < comp + THRESH_FLOAT)
		return (true);
	else
		return (false);
} */

/* vector_dot_product:
*	Calculates the dot product between the two
*	points p1 and p2.
*
*	Return: The calculated dot product.
*/
/* float	vec3_dot(t_coordinates p1, t_coordinates p2)
{
	return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
} */

/* vec3_sub:
*	Calculate the difference of the tuple of the x, y and 
*	z values of p1 and p2.
*
*	Return: the calculated point.
*/
/* t_coordinates	vec3_sub(t_coordinates p1, t_coordinates p2)
{
	t_coordinates	p;

	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	p.z = p1.z - p2.z;
	return (p);
} */

/* vec3_add:
*	Calculate the sum of the tuple of the x, y and 
*	z values of p1 and p2.
*
*	Return: the calculated point.
*/
/* t_coordinates	vec3_add(t_coordinates p1, t_coordinates p2)
{
	t_coordinates	p;

	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	p.z = p1.z + p2.z;
	return (p);
} */

/* vec3_multiply_const:
*	Multiply a point p1 by a const nbr to shift
*	the point.
*
*	Return: the new shifted point.
*/
/* t_coordinates	vec3_multiply_const(t_coordinates p1, float nbr)
{
	t_coordinates	p;

	p.x = p1.x * nbr;
	p.y = p1.y * nbr;
	p.z = p1.z * nbr;
	return (p);
} */

/* vector_cross:
*	Calculates the cross product between two vectors
*	to find the vector which is orthogonal to p1 and p2.
*
*	Return: The orthogonal vector.
*/
/* t_coordinates	vec3_cross(t_coordinates p1, t_coordinates p2)
{
	t_coordinates	v;

	v.x = p1.y * p2.z - p1.z * p2.y;
	v.y = p1.z * p2.x - p1.x * p2.z;
	v.z = p1.x * p2.y - p1.y * p2.x;
	return (v);
} */

/* vec3_get_pt:
*	Calculates the point on the line v(d).
*
*	Return: the point v(d).
*/
/* t_coordinates	vec3_get_pt(t_vector v, float d)
{
	t_coordinates	p;

	p.x = v.origin.x + d * v.v_norm.x;
	p.y = v.origin.y + d * v.v_norm.y;
	p.z = v.origin.z + d * v.v_norm.z;
	return (p);
} */

/* vec3_dist_pts:
*	Calculates the distance between two points.
*
*	Return: distance between the points.
*/
/* float	vec3_dist_pts(t_coordinates p1, t_coordinates p2)
{
	return (sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2) + powf(p1.z - p2.z, 2)));
} */

/* vec3_pt_on_line:
*	Checks if the point p lies behind the origin 
*	of v, concerning to the v_norm of v.
*
*	Return: TRUE if p lies on the line of v and
*		otherwise FALSE.
*/
/* int	vec3_pt_on_line(t_vector v, t_coordinates p)
{
	if ((p.x - v.origin.x > 0 && v.v_norm.x < 0) 
		|| (p.x - v.origin.x < 0 && v.v_norm.x > 0))
		return (false);
	if ((p.y - v.origin.y > 0 && v.v_norm.y < 0) 
		|| (p.y - v.origin.y < 0 && v.v_norm.y > 0))
		return (false);
	if ((p.z - v.origin.z > 0 && v.v_norm.z < 0) 
		|| (p.z - v.origin.z < 0 && v.v_norm.z > 0))
		return (false);
	return (true);
} */

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
*	If t is negative, the hit points lies behind
*	the origin. If t is 0, the hit points and the
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
	float	a;
	float	b;
	float	c;
	float	t[2];

	a = powf(ray.v_norm.x, 2) + powf(ray.v_norm.y, 2) 
		+ powf(ray.v_norm.z, 2);
	b = 2 * (ray.v_norm.x * (ray.origin.x - sphere.center->x) 
			+ ray.v_norm.y * (ray.origin.y - sphere.center->y) 
			+ ray.v_norm.z * (ray.origin.z - sphere.center->z));
	c = powf((ray.origin.x - sphere.center->x), 2) 
		+ powf((ray.origin.y - sphere.center->y), 2) 
		+ powf((ray.origin.z - sphere.center->z), 2) 
		- powf((sphere.d / 2), 2);
	t[0] = (-b + sqrtf(powf(b, 2) - 4 * a * c)) / (2 * a);
	t[1] = (-b - sqrtf(powf(b, 2) - 4 * a * c)) / (2 * a);
	if ((t[0] < THRESH_FLOAT && t[1] < THRESH_FLOAT) || isnan(t[0]) || isnan(t[1]))
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
*		- the origin of the ray lies on the plane: the 
*			origin is defined as intersection point.
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

	// TEST: ray lies on plane
	//	Expected: no hit (return false) - initializing hit doesn't matter

	tmp.x = plane.point->x - ray.origin.x;
	tmp.y = plane.point->y - ray.origin.y;
	tmp.z = plane.point->z - ray.origin.z;
	numer = vec3_dot(tmp, *plane.v_norm);
	denom = vec3_dot(ray.v_norm, *plane.v_norm);
	if (equal(denom, 0))
	{
		if (equal(numer, 0))
		{
			hit->p1 = ray.origin;
			hit->p2 = ray.origin;
			return (true);
		}
		else
			return (false);
	}
	d = numer / denom;
	if (!vec3_pt_on_line(ray, vec3_get_pt(ray, d)))
		return (false);
	hit->p1 = vec3_get_pt(ray, d);
	hit->p2 = hit->p1;
	return (true);
}

/* intersect_tube_inter:
*
*
*	Return: 0 if both points are out-of-range of the height,
*		1 if only p1 is in the range of the height,
*		2 if only p2 is in the range of the height and
*		3 if both points are in the range of the height.
*/
int	intersect_tube_inter(float h[2], t_cylinder cyl, float (*t)[2])
{
	if ((h[0] > cyl.h || h[0] < 0) && (h[1] > cyl.h || h[1] < 0))
		return (0);
	else if (h[0] > cyl.h || h[0] < 0)
	{
		(*t)[0] = (*t)[1];
		return (2);
	}
	else if (h[1] > cyl.h || h[1] < 0)
	{
		(*t)[1] = (*t)[0];
		return (1);
	}
	else
		return (3);
}

/* intersect_tube:
*
*/
int	intersect_tube(t_cylinder cyl, t_vector ray, t_hit *hit)
{
	float	abc[3];
	float	d;
	float	h[2];
	float	t[2];
	t_coordinates	orth;
	t_coordinates	v;
	int		nbr_inter;

	nbr_inter = 0;
	orth = vec3_cross(ray.v_norm, *cyl.v_norm);
	abc[0] = vec3_dot(orth, orth);
	v = vec3_cross(vec3_sub(ray.origin, *cyl.center), *cyl.v_norm);
	abc[1] = 2 * vec3_dot(orth, v);
	abc[2] = vec3_dot(v, v) - powf(cyl.d / 2, 2);
	d = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (d < 0 || abc[0] < THRESH_FLOAT)
		return (nbr_inter);
	d = sqrtf(d);
	t[0] = (-abc[1] + d) / (2 * abc[0]);
	t[1] = (-abc[1] - d) / (2 * abc[0]);
	h[0] = vec3_dot(vec3_sub(vec3_add(ray.origin, 
			vec3_multiply_const(ray.v_norm, t[0])), *cyl.center), *cyl.v_norm);
	h[1] = vec3_dot(vec3_sub(vec3_add(ray.origin, 
			vec3_multiply_const(ray.v_norm, t[1])), *cyl.center), *cyl.v_norm);
	nbr_inter = 0;
	if (intersect_tube_inter(h, cyl, &t) == 1 
		&& vec3_pt_on_line(ray, vec3_get_pt(ray, t[0])))
	{
		hit->p1 = vec3_get_pt(ray, t[0]);
		hit->p2 = hit->p1;
		nbr_inter = 1;
	}
	else if (intersect_tube_inter(h, cyl, &t) == 2  
		&& vec3_pt_on_line(ray, vec3_get_pt(ray, t[1])))
	{
		hit->p2 = vec3_get_pt(ray, t[1]);
		hit->p1 = hit->p2;
		nbr_inter = 1;
	}
	else if (intersect_tube_inter(h, cyl, &t) == 3 
		&& vec3_pt_on_line(ray, vec3_get_pt(ray, t[0])) 
		&& vec3_pt_on_line(ray, vec3_get_pt(ray, t[1])))
	{
		hit->p1 = vec3_get_pt(ray, t[0]);
		hit->p2 = vec3_get_pt(ray, t[1]);
		nbr_inter = 2;
	}
	else if (intersect_tube_inter(h, cyl, &t) == 3 
		&& vec3_pt_on_line(ray, vec3_get_pt(ray, t[0])) 
		&& !vec3_pt_on_line(ray, vec3_get_pt(ray, t[1])))
	{
		hit->p1 = vec3_get_pt(ray, t[0]);
		hit->p2 = hit->p1;
		nbr_inter = 1;
	}
	else if (intersect_tube_inter(h, cyl, &t) == 3 
		&& !vec3_pt_on_line(ray, vec3_get_pt(ray, t[0])) 
		&& vec3_pt_on_line(ray, vec3_get_pt(ray, t[1])))
	{
		hit->p2 = vec3_get_pt(ray, t[1]);
		hit->p1 = hit->p2;
		nbr_inter = 1;
	}
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
