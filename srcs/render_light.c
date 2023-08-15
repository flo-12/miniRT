/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:03:56 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/14 12:03:58 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* get_intensity:
*	Calculate the RGB values to display multiplied with 
*	the intensity. If BONUS==0, the color of the light is
*	set to white (RGB) and otherwise the RGB values are
*	also considered.
*
*	Return: calculated RGB values with the considered
*		intensity and color of the light and object.
*/
t_color	get_intensity(float intensity, t_color c_obj, t_color c_light, bool debug)
{
	t_color	color;

	if (BONUS)
	{
		color.r = c_obj.r * (intensity * ((float)c_light.r / 255));
		color.g = c_obj.g * (intensity * ((float)c_light.g / 255));
		color.b = c_obj.b * (intensity * ((float)c_light.b / 255));
	}
	else
	{
		color.r = (int)((float)c_obj.r * (intensity * 1));
		color.g = (int)((float)c_obj.g * (intensity * 1));
		color.b = (int)((float)c_obj.b * (intensity * 1));
	}
	if (debug)
		printf("color_obj(%d,%d,%d) | intensity=%f | color_light(%d,%d,%d) | color(%d,%d,%d)\n",
			c_obj.r, c_obj.g, c_obj.b, intensity, c_light.r, c_light.g, c_light.b, color.r, color.g, color.b);
	return (color);
}

/* get_norm_cyl:
*	Calculates the normalized vector for the surface normal
*	of a cylinder by differentiating between the cap and the
*	tube of the cylinder with the following steps:
*		1) calculate the distance l (in direction of v_norm of
*			cylinder) of the hit point to the cylinder's
*			center
*		2) If cap: l is equal to 0 or the height of the cylinder
*		3) If tube: otherwise
*			- get the point p which is l away from the cylinder's
*				center in the direction of v_norm
*			- calculate the normalized vector of the surface
*				(identical to sphere with p being the center of
*				the sphere)
*
*	Return: the normalized surface vector.
*/
t_coordinates	get_surface_norm_cyl(t_cylinder cyl, t_vector shadow)
{
	t_coordinates	norm_obj;
	float			l;
	t_coordinates	p;

	l = sqrtf(powf(vec3_dist_pts(shadow.origin, *cyl.center), 2) 
			- powf(cyl.d / 2, 2));
	if (equal(l, 0) || equal(l, cyl.h))
		norm_obj = *cyl.v_norm;
	else
	{
		p = vec3_add(*cyl.center, vec3_multiply_const(*cyl.v_norm, l));
		norm_obj = vec3_norm(vec3_sub(shadow.origin, p));
	}
	return (norm_obj);
}

/* get_obj_color:
*	Get the color of the object.
*
*	Return: color of the object.
*/
t_color	get_obj_color(t_object obj)
{
	if (obj.identifier == PLANE)
		return (*obj.u_obj.plane.color);
	else if (obj.identifier == SPHERE)
		return (*obj.u_obj.sphere.color);
	else
		return (*obj.u_obj.cylinder.color);
}

/* render_light:
*	Calculates the light (RGB) for an object and it's shadow
*	ray to the light. The origin of the shadow ray equals
*	the intersection point with the object.
*	The following steps are executed:
*		1) get the normalized vector for the surface (dependened)
*			on the object identifier)
*		2) Calculate the angle alpha between the surface vector
*			and the shadow ray
*		3) If alpha is smaller or equal to 0, no light is
*			absorbed (color=[0,0,0])
*		4) If alpha is greater than 0, the intensity in
*			dependency of the color of the object and the light
*			(bonus) are calculated
*
*	Return: the light as t_color (RGB values).
*/
t_color	render_light(t_object obj, t_light light, t_vector shadow, bool debug)
{
	t_color			color_obj;
	t_coordinates	norm_obj;
	float			alpha;

	color_obj = get_obj_color(obj);
	if (obj.identifier == PLANE)
		norm_obj = *obj.u_obj.plane.v_norm;
	else if (obj.identifier == SPHERE)
		norm_obj = vec3_norm(vec3_sub(shadow.origin, *obj.u_obj.sphere.center));
	else// if (obj.identifier == CYLINDER)
		norm_obj = get_surface_norm_cyl(obj.u_obj.cylinder, shadow);
	alpha = vec3_dot(norm_obj, shadow.v_norm);
	if (alpha > 0)
		return (get_intensity(alpha, 
				color_obj, *light.color, debug));
	else
		return (get_intensity(0, color_obj, *light.color, debug));
}
