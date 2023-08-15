/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:39:36 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/15 11:39:38 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
