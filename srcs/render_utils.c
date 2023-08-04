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

//#include "miniRT.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../includes/miniRT_define.h"

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

}

int	main()
{
	t_coordinates	v;
	t_coordinates	v_norm;

	v.x = 3; v.y = 4; v.z = 5;
	v_norm = vector_normalize(v);
	printf("v_norm=(%f, %f, %f)\n", v_norm.x, v_norm.y, v_norm.z);
	return (0);
}
