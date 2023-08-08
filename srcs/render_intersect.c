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

//#include "miniRT.h"



#include "../includes/miniRT_define.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

/* equal:
*	Checks if two float numbers (nbr and comp) are equal,
*	whereas nbr lies in a range of comp+-THRESH_FLOAT.
*	This is done due to comparison / rounding problems
*	with floats.
*
*	Return: TRUE if the numbers are equal and FALSE
*		otherwise.
*/
bool	equal(float nbr, float comp)
{
	if (nbr > comp - THRESH_FLOAT && nbr < comp + THRESH_FLOAT)
		return (true);
	else
		return (false);
}

/* vector_dot_product:
*	Calculates the dot product between the two
*	points p1 and p2.
*
*	Return: The calculated dot product.
*/
float	vec3_dot(t_coordinates p1, t_coordinates p2)
{
	return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
}

t_coordinates	vec3_sub(t_coordinates p1, t_coordinates p2)
{
	t_coordinates	p;

	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	p.z = p1.z - p2.z;
	return (p);
}

t_coordinates	vec3_add(t_coordinates p1, t_coordinates p2)
{
	t_coordinates	p;

	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	p.z = p1.z + p2.z;
	return (p);
}

t_coordinates	vec3_multiply_const(t_coordinates p1, float nbr)
{
	t_coordinates	p;

	p.x = p1.x * nbr;
	p.y = p1.y * nbr;
	p.z = p1.z * nbr;
	return (p);
}

/* vector_cross:
*	Calculates the cross product between two vectors
*	to find the vector which is orthogonal to p1 and p2.
*
*	Return: The orthogonal vector.
*/
t_coordinates	vec3_cross(t_coordinates p1, t_coordinates p2)
{
	t_coordinates	v;

	v.x = p1.y * p2.z - p1.z * p2.y;
	v.y = p1.y * p2.x - p1.x * p2.z;
	v.z = p1.x * p2.y - p1.y * p2.x;
	return (v);
}

t_coordinates	vec3_get_pt(t_vector v, float d)
{
	t_coordinates	p;

	p.x = v.origin.x + d * v.v_norm.x;
	p.y = v.origin.y + d * v.v_norm.y;
	p.z = v.origin.z + d * v.v_norm.z;
	return (p);
}

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
	hit->p1 = vec3_get_pt(ray, d);
	hit->p2 = hit->p1;
	return (true);
}

/* intersect_tube_inter:
*
*/
int	intersect_tube_inter(float h[2], t_cylinder cyl, float (*t)[2])
{
	if ((h[0] > cyl.h || h[0] < 0) && (h[1] > cyl.h || h[1] < 0))
		return (0);
	else if (h[0] > cyl.h || h[0] < 0)
	{
		(*t)[0] = (*t)[1];
		return (1);
	}
	else if (h[1] > cyl.h || h[1] < 0)
	{
		(*t)[1] = (*t)[0];
		return (1);
	}
	else
		return (2);
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
	nbr_inter = intersect_tube_inter(h, cyl, &t);
	if (!nbr_inter)
		return (nbr_inter);
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
	t_hit	*hit_tmp;

	nbr_inter = intersect_tube(cyl, ray, hit);
	if (nbr_inter == 2)
		return (true);
	hit_tmp = hit;

	/* t_plane	pl1;
	pl1.point = cyl.center;
	t_coordinates	pl2_v_norm = vec3_sub(*pl1.point, vec3_multiply_const(*cyl.v_norm, vec3_dot(*pl1.point, *cyl.v_norm)));
	t_plane	pl2;
	t_coordinates	pl2_point = vec3_add(vec3_multiply_const(*cyl.v_norm, cyl.h), *cyl.center);
	t_coordinates	pl2_v_norm = vec3_sub(*pl2.point, vec3_multiply_const(*cyl.v_norm, vec3_dot(*pl2.point, *cyl.v_norm)));

	
	(t_plane){a.x + b.x, a.y + b.y, a.z + b.z} */

	if (intersect_plane((t_plane){cyl.center, cyl.v_norm, cyl.color}, ray, hit))
	{
		nbr_inter++;
		if (nbr_inter == 2)
		{
			hit->p1 = hit_tmp->p1;
			return (true);
		}
		else
			hit_tmp = hit;
	}
	t_coordinates	p = vec3_add(vec3_multiply_const(*cyl.v_norm, cyl.h), *cyl.center);
	if (intersect_plane((t_plane){&p, cyl.v_norm, cyl.color}, ray, hit))
	{
		nbr_inter++;
		hit->p1 = hit_tmp->p1;
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
/* int	render_intersect(t_object obj, t_vector ray, t_hit *hit)
{

} */

int	main()
{
	t_sphere	sphere;
	t_plane		plane; plane.point = malloc(sizeof(t_coordinates)); plane.v_norm = malloc(sizeof(t_coordinates));
	t_cylinder	cylinder; cylinder.center = malloc(sizeof(t_coordinates)); cylinder.v_norm = malloc(sizeof(t_coordinates));
	t_vector	ray;
	t_hit		hit;

	printf("\n**** SPHERE ****\n");
	sphere.center->x = 0; sphere.center->y = 0; sphere.center->z = 0;
	sphere.d = 1;
	ray.origin.x = 10; ray.origin.y = 10; ray.origin.z = 10;
	ray.v_norm.x = 1; ray.v_norm.y = 0; ray.v_norm.z = 0;
	if (intersect_sphere(sphere, ray, &hit))
		printf("Intersection Points P1=(%f, %f, %f) and P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("No intersection...\n");

	/* printf("\n**** PLANE (intersection) ****\n");
	plane.point->x = 0; plane.point->y = 0; plane.point->z = 0;
	plane.v_norm->x = 0; plane.v_norm->y = 1; plane.v_norm->z = 0;
	ray.origin.x = 1; ray.origin.y = 2; ray.origin.z = 3;
	ray.v_norm.x = 0.5; ray.v_norm.y = 0.5; ray.v_norm.z = -0.5;
	if (intersect_plane(plane, ray, &hit))
		printf("Intersection Points P1=(%f, %f, %f) and P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("No intersection...\n");

	printf("\n**** PLANE (overlapping) ****\n");
	plane.point->x = 0; plane.point->y = 0; plane.point->z = 0;
	plane.v_norm->x = 0; plane.v_norm->y = 1; plane.v_norm->z = 0;
	ray.origin.x = 0.5; ray.origin.y = 0; ray.origin.z = 0.5;
	ray.v_norm.x = 0.5; ray.v_norm.y = 0; ray.v_norm.z = 0.5;
	if (intersect_plane(plane, ray, &hit))
		printf("Intersection Points P1=(%f, %f, %f) and P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("No intersection...\n");

	printf("\n**** PLANE (parallel) ****\n");
	plane.point->x = 0; plane.point->y = 0; plane.point->z = 0;
	plane.v_norm->x = 0; plane.v_norm->y = 1; plane.v_norm->z = 0;
	ray.origin.x = 1; ray.origin.y = 2; ray.origin.z = 3;
	ray.v_norm.x = 0.5; ray.v_norm.y = 0; ray.v_norm.z = 0.5;
	if (intersect_plane(plane, ray, &hit))
		printf("Intersection Points P1=(%f, %f, %f) and P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("No intersection...\n"); */
	
	printf("\n**** CYLINDER (intersection) ****\n");
	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 4;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = 1; ray.origin.y = 1; ray.origin.z = -2;
	ray.v_norm.x = 0; ray.v_norm.y = 0; ray.v_norm.z = 1;
	int	nbr_inter = intersect_cylinder(cylinder, ray, &hit);
	if (nbr_inter)
		printf("Intersection Points P1=(%f, %f, %f) and P2=(%f, %f, %f) and %d intersection(s).\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z, nbr_inter);
	else
		printf("No intersection...\n");

	printf("\n");
	return (0);
}