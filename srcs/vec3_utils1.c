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
