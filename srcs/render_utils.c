/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:54:06 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/04 13:54:08 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* vector_normalize:
*	Normalizes the direction vector in the arguments.
*
*	Return: the normalized vector.
*/
t_coordinates	vector_normalize(t_coordinates v)
{
	t_coordinates	v_norm;
	float			magnitude;

	magnitude = sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
	v_norm.x = v.x / magnitude;
	v_norm.y = v.y / magnitude;
	v_norm.z = v.z / magnitude;
	return (v_norm);
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

/* distance_points:
*	Calculates the distance between the two points
*	p1 and p2.
*
*	Return: Calculated distance.
*/
float	distance_points(t_coordinates p1, t_coordinates p2)
{
	return (sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2) 
			+ powf(p1.z - p2.z, 2)));
}

/* get_vector_direction:
*	Calculates the direction vector between p1 and p2.
*
*	Return: direction vector from p1 to p2.
*/
t_coordinates	get_vector_direction(t_coordinates p1, t_coordinates p2)
{
	t_coordinates	v;

	v.x = p2.x - p1.x;
	v.y = p2.y - p1.y;
	v.z = p2.z - p1.z;
	return (v);
}
