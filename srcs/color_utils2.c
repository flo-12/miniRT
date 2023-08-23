/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:46:18 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/22 16:46:20 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* color_sphere:
*	Get the color of the sphere.
*
*	Return: color of the sphere.
*/
t_color	color_sphere(t_object obj)
{
	return (*obj.u_obj.sphere.color);
}

/* color_plane:
*	Get the color of the plane.
*
*	Return: color of the plane.
*/
t_color	color_plane(t_object obj)
{
	return (*obj.u_obj.plane.color);
}

/* color_cylinder:
*	Get the color of the cylinder.
*
*	Return: color of the cylinder.
*/
t_color	color_cylinder(t_object obj)
{
	return (*obj.u_obj.cylinder.color);
}

/* color_cone:
*	Get the color of the cone.
*
*	Return: color of the cone.
*/
t_color	color_cone(t_object obj)
{
	return (*obj.u_obj.cone.color);
}
