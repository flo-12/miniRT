/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:38:01 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/11 12:53:16 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

/* vec3_angle
returns the angle between two vectors.

Return: the angle in rad
*/
float	vec3_angle_rad(t_coordinates v1, t_coordinates v2)
{
	return (acosf(vec3_dot(v1, v2)));
}

float	vec3_angle_deg(t_coordinates v1, t_coordinates v2)
{
	return (vec3_angle_rad(v1, v2) * 180 / M_PI);
}

/* vec3_sub:
*	Calculate the difference of the tuple of the x, y and 
*	z values of p1 and p2.
*
*	Return: the calculated point.
*/
t_coordinates	vec3_sub(t_coordinates p1, t_coordinates p2)
{
	t_coordinates	p;

	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	p.z = p1.z - p2.z;
	return (p);
}

/* vec3_add:
*	Calculate the sum of the tuple of the x, y and 
*	z values of p1 and p2.
*
*	Return: the calculated point.
*/
t_coordinates	vec3_add(t_coordinates p1, t_coordinates p2)
{
	t_coordinates	p;

	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	p.z = p1.z + p2.z;
	return (p);
}

/* vec3_multiply_const:
*	Multiply a point p1 by a const nbr to shift
*	the point.
*
*	Return: the new shifted point.
*/
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
	v.y = p1.z * p2.x - p1.x * p2.z;
	v.z = p1.x * p2.y - p1.y * p2.x;
	return (v);
}

/* vec3_get_pt:
*	Calculates the point on the line v(d).
*
*	Return: the point v(d).
*/
t_coordinates	vec3_get_pt(t_vector v, float d)
{
	t_coordinates	p;

	p.x = v.origin.x + d * v.v_norm.x;
	p.y = v.origin.y + d * v.v_norm.y;
	p.z = v.origin.z + d * v.v_norm.z;
	return (p);
}

/* vec3_dist_pts:
*	Calculates the distance between two points.
*
*	Return: distance between the points.
*/
float	vec3_dist_pts(t_coordinates p1, t_coordinates p2)
{
	return (sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2) 
		+ powf(p1.z - p2.z, 2)));
}

/* vec3_pt_on_line:
*	Checks if the point p lies behind the origin 
*	of v, concerning to the v_norm of v.
*
*	Return: TRUE if p lies on the line of v and
*		otherwise FALSE.
*/
int	vec3_pt_on_line(t_vector v, t_coordinates p)
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
}

/* vector_normalize:
*	Normalizes the direction vector in the arguments.
*
*	Return: the normalized vector.
*/
t_coordinates	vec3_norm(t_coordinates v)
{
	t_coordinates	v_norm;
	float			magnitude;

	magnitude = sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
	v_norm.x = v.x / magnitude;
	v_norm.y = v.y / magnitude;
	v_norm.z = v.z / magnitude;
	return (v_norm);
}

/* vec3_get_dir:
*	Calculates the direction vector between p1 and p2.
*
*	Return: direction vector from p1 to p2.
*/
t_coordinates	vec3_get_dir(t_coordinates p1, t_coordinates p2)
{
	t_coordinates	v;

	v.x = p2.x - p1.x;
	v.y = p2.y - p1.y;
	v.z = p2.z - p1.z;
	return (v);
}
