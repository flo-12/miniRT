/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:03:56 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/23 18:10:07 by lwidmer          ###   ########.fr       */
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
t_color	get_intensity(float intensity, t_color c_obj, t_color c_light,
	bool ambient)
{
	t_color	color;

	if (intensity > 1)
		intensity = 1;
	if (BONUS || ambient)
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
	return (color);
}

/*
renders the pecular light component based on the blinn-phong model.
this model computes the halfway vector between primary ray (Intersection
to camera) and shadow ray (Intersection to Light).
and then computes the specular component based on the angle between halfway
vector and surface normal.

return: t_color
*/
float	get_specular_intensity(t_global global, t_coordinates shadow_ray,
		t_coordinates p_hit, t_coordinates norm_obj)
{
	t_coordinates	halfway_vector;
	t_coordinates	primary_ray;
	float			alpha;

	alpha = 0;
	if (BONUS)
	{
		primary_ray = vec3_norm(vec3_get_dir(p_hit, *global.camera->point));
		halfway_vector = vec3_norm(vec3_add(primary_ray, shadow_ray));
		alpha = powf(vec3_dot(norm_obj, halfway_vector), 30);
	}
	return (alpha);
}

float	get_diffuse_intensity(t_coordinates norm_obj, t_coordinates shadow_ray)
{
	float	alpha;

	alpha = vec3_dot(norm_obj, shadow_ray);
	return (alpha);
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
t_color	render_light(t_object obj, t_global global, t_vector shadow, 
						t_coordinates p_hit)
{
	t_color			color_obj;
	t_coordinates	norm_obj;
	float			intensity;

	color_obj = obj.fct_color(obj);
	norm_obj = (*obj.fct_surface_norm)(obj, shadow);
	intensity = get_diffuse_intensity(norm_obj, shadow.v_norm)
		+ get_specular_intensity(global, shadow.v_norm,
			p_hit, norm_obj);
	intensity = intensity * global.light->brightness;
	if (intensity > 0)
		return (get_intensity(intensity, color_obj, *global.light->color,
				false));
	else
		return (get_intensity(0, color_obj, *global.light->color, false));
}
