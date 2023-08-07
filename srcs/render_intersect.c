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
	hit->p1.x = ray.origin.x + t[0] * ray.v_norm.x;
	hit->p1.y = ray.origin.y + t[0] * ray.v_norm.y;
	hit->p1.z = ray.origin.z + t[0] * ray.v_norm.z;
	hit->p2.x = ray.origin.x + t[1] * ray.v_norm.x;
	hit->p2.y = ray.origin.y + t[1] * ray.v_norm.y;
	hit->p2.z = ray.origin.z + t[1] * ray.v_norm.z;
	return (true);
}

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
float	vector_dot_product(t_coordinates p1, t_coordinates p2)
{
	return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
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
	numer = vector_dot_product(tmp, *plane.v_norm);
	denom = vector_dot_product(ray.v_norm, *plane.v_norm);
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
	hit->p1.x = ray.origin.x + d * ray.v_norm.x;
	hit->p1.y = ray.origin.y + d * ray.v_norm.y;
	hit->p1.z = ray.origin.z + d * ray.v_norm.z;
	hit->p2 = hit->p1;
	return (true);
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
	float	a;
	float	b;
	float	c;
	float	t[2];

	// a is wrong
	a = powf(ray.v_norm.x, 2) + powf(ray.v_norm.y, 2) + powf(ray.v_norm.z, 2) - powf(cyl.h, 2);
	b = 2 * ((ray.origin.x - cyl.center->x) * ray.v_norm.x
			+ (ray.origin.y - cyl.center->y) * ray.v_norm.y
			+ (ray.origin.z - cyl.center->z) * ray.v_norm.z);
	c = powf(ray.origin.x - cyl.center->x, 2) + powf(ray.origin.y - cyl.center->y, 2) 
		+ powf(ray.origin.z - cyl.center->z, 2) 
		- powf(cyl.d / 2, 2) * (powf(ray.v_norm.x, 2) + powf(ray.v_norm.y, 2));
	if (powf(b, 2) - 4 * a * c < -THRESH_FLOAT)
		return (false);	// only for cylindric part
	t[0] = (-b + sqrtf(powf(b, 2) - 4 * a * c)) / (2 * a);
	t[1] = (-b - sqrtf(powf(b, 2) - 4 * a * c)) / (2 * a);
printf("a=%f | b=%f | c=%f | t(%f, %f)\n", a, b, c, t[0], t[1]);
	if (!(t[0] >= 0 && t[0] <= cyl.h) && !(t[1] >= 0 && t[1] <= cyl.h) 
		|| isnan(t[0]) || isnan(t[1]))
		return (false);
	else if (!(t[0] >= 0 && t[0] <= cyl.h))
		t[0] = t[1];
	else if (!(t[1] >= 0 && t[1] <= cyl.h))
		t[1] = t[0];
	hit->p1.x = ray.origin.x + t[0] * ray.v_norm.x;
	hit->p1.y = ray.origin.y + t[0] * ray.v_norm.y;
	hit->p1.z = ray.origin.z + t[0] * ray.v_norm.z;
	hit->p2.x = ray.origin.x + t[1] * ray.v_norm.x;
	hit->p2.y = ray.origin.y + t[1] * ray.v_norm.y;
	hit->p2.z = ray.origin.z + t[1] * ray.v_norm.z;
	return (true);
	// tbd: planes at the ends of the cylindric part have to be included...
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
	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = 5;
	cylinder.d = 4;
	cylinder.h = 6;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = 0; ray.origin.y = 0; ray.origin.z = 0;
	ray.v_norm.x = 1; ray.v_norm.y = 1; ray.v_norm.z = 1;
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("Intersection Points P1=(%f, %f, %f) and P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("No intersection...\n");

	printf("\n");
	return (0);
}