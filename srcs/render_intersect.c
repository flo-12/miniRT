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

//void	intersect_sphere(float *E, float *D, float I[2][3])
t_hit	intersect_sphere(t_sphere sphere, t_vector ray)
{
	// aktueller Stand: nur Einheits-Kugel (c(0,0,0), r=2)
	t_hit	hit;
	float	a;
	float	b;
	float	c;
	float	t[2];
	
	a = powf(ray.v_norm.x, 2) + powf(ray.v_norm.y, 2) 
			+ powf(ray.v_norm.z, 2);
	b = 2 * (ray.origin.x * ray.v_norm.x + ray.origin.y * ray.v_norm.y 
			+ ray.origin.z * ray.v_norm.z);
	c = powf(ray.origin.x 2) + powf(ray.origin.y, 2) 
			+ powf(ray.origin.z, 2) - 1;
	t[0] = (-b + sqrtf(pow(b, 2) - 4 * a * c)) / (2 * a);
	t[1] = (-b - sqrtf(pow(b, 2) - 4 * a * c)) / (2 * a);
	
	hit.p1.x = ray.origin.x + t[0] * ray.v_norm.x;
	hit.p1.y = ray.origin.y + t[0] * ray.v_norm.y;
	hit.p1.z = ray.origin.z + t[0] * ray.v_norm.z;
	hit.p2.x = ray.origin.x + t[1] * ray.v_norm.x;
	hit.p2.y = ray.origin.y + t[1] * ray.v_norm.y;
	hit.p2.z = ray.origin.z + t[1] * ray.v_norm.z;
	
	return (hit);
}

/* intersect:
*	Calculates the intersection points (2 points)
*	between an object and a ray.
*	Differentiates between different types of
*	objects.
*
*	Return: struct with the two intersection points.
*		If only one intersection point is found, the
*		two points are equal.
*/
t_hit	render_intersect(t_object obj, t_vector ray)
{

}
