/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_inter_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:11:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/25 09:32:07 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
checks whether the intersections that were found are below the threshhold
or not existing. if there is only one intersection, both hitpoints are set
to be equal.
lastly checks the angle between the cone orientation and the hitpoint. If this
angle is bigger than 180 degree, the dot product becomes negative and we
return false.
RETURN: bool (true if there are valid intersections)
*/

bool	cone_get_hitpoints(t_cone cone, t_vector ray, t_hit *hit, float t[2])
{
	if ((t[0] < THRESH_FLOAT && t[1] < THRESH_FLOAT) 
		|| isnan(t[0]) || isnan(t[1]))
		return (false);
	else if (t[0] < THRESH_FLOAT)
		t[0] = t[1];
	else if (t[1] < THRESH_FLOAT)
		t[1] = t[0];
	hit->p1 = vec3_get_pt(ray, t[0]);
	hit->p2 = vec3_get_pt(ray, t[1]);
	if (vec3_dot(vec3_sub(hit->p1, *cone.vertex), *cone.v_norm) <= 0)
		return (false);
	return (true);
}

/*
m is the ratio between the squared radius and height of the cone. Although our
cone technically does not hav a height, the radius is calculated for a height
of one to obtain this ratio.
*/
bool	intersect_cone(t_object obj, t_vector ray, t_hit *hit)
{
	t_cone			cone;
	t_coordinates	origin_to_vertex;
	float			m;
	float			abc[3];
	float			dt[4];

	cone = obj.u_obj.cone;
	m = powf(tanf(deg_to_rad(cone.angle / 2)), 2);
	origin_to_vertex = vec3_sub(ray.origin, *cone.vertex);
	dt[0] = vec3_dot(ray.v_norm, *cone.v_norm);
	dt[1] = vec3_dot(origin_to_vertex, *cone.v_norm);
	abc[0] = vec3_dot(ray.v_norm, ray.v_norm) - m * powf(dt[0], 2)
		- powf(dt[0], 2);
	abc[1] = 2 * (vec3_dot(ray.v_norm, origin_to_vertex) - m * dt[0] * dt[1]
			- dt[0] * dt[1]);
	abc[2] = vec3_dot(origin_to_vertex, origin_to_vertex) - m * powf(dt[1], 2)
		- powf(dt[1], 2);
	dt[2] = (-abc[1] - sqrtf(powf(abc[1], 2) - (4 * abc[0] * abc[2])))
		/ (2 * abc[0]);
	dt[3] = (-abc[1] + sqrtf(powf(abc[1], 2) - (4 * abc[0] * abc[2])))
		/ (2 * abc[0]);
	return (cone_get_hitpoints(cone, ray, hit, dt + 2));
}
