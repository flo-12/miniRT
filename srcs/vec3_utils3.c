/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:47:14 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/15 11:47:15 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* vec3_angle_rad:
*	Calculates the angle between two vectors.
*
*	Return: the angle in rad
*/
float	vec3_angle_rad(t_coordinates v1, t_coordinates v2)
{
	return (acosf(vec3_dot(v1, v2)));
}

/* vec3_angle_deg:
*	Calculates the angle between two vectors.
*
*	Return: the angle in degree
*/
float	vec3_angle_deg(t_coordinates v1, t_coordinates v2)
{
	return (vec3_angle_rad(v1, v2) * 180 / M_PI);
}
