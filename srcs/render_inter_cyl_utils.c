/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_inter_tube_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:05:21 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/10 17:05:23 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* tube_valid_height:
*	Checks if the intersection point at t is in
*	the range of the height of the tube.
*
*	Return: TRUE if t is valid and FALSE otherwise.
*/
bool	tube_valid_height(t_vector ray, float t, t_cylinder cyl)
{
	float	h;

	h = vec3_dot(vec3_sub(vec3_get_pt(ray, t), *cyl.center), *cyl.v_norm);
	if (h <= cyl.h && h >= 0)
		return (true);
	else
		return (false);
}

/* tube_valid_dir:
*	Checks if the intersection point at t is in
*	the direction of the ray and doesn't lie behind
*	the origin of the ray.
*
*	Return: TRUE if t is valid and FALSE otherwise. 
*/
bool	tube_valid_dir(t_vector ray, float t)
{
	if (vec3_pt_on_line(ray, vec3_get_pt(ray, t)))
		return (true);
	else
		return (false);
}

/* tube_check_valid_points:
*	Checks if the points at t[0] and t[1] are valid
*	in respect to the height of the cylinder and the
*	direction of the ray.
*	If a point at t is not valid and the other t-value
*	gives a valid result, the not valid result is
*	overwritten by the valid result. E.g.:
*		if (not_valid(t[0]) && valid(t[1]))
*			t[0] = t[1];
*	If both are valid or not valid, nothing is changed.
*
*	Return: The amount of valid t values.
*/
int	tube_check_valid_points(t_vector ray, float (*t)[2], t_cylinder cyl)
{
	bool	valid[2];

	valid[0] = tube_valid_height(ray, (*t)[0], cyl) 
		&& tube_valid_dir(ray, (*t)[0]);
	valid[1] = tube_valid_height(ray, (*t)[1], cyl) 
		&& tube_valid_dir(ray, (*t)[1]);
	if (valid[0] && valid[1])
		return (2);
	else if (valid[0])
	{
		(*t)[1] = (*t)[0];
		return (1);
	}
	else if (valid[1])
	{
		(*t)[0] = (*t)[1];
		return (1);
	}
	else
		return (0);
}
