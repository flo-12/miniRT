/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_inter_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:11:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/22 19:58:27 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*

theta is half the cones opening angle
*/
bool	render_cone(t_object obj, t_vector ray, t_hit *hit)
{
	float			abc[3];
	float			t[2];
	float			d;
	float			theta;
	t_coordinates	origin_to_vertex;
	t_cone			cone;

	cone = obj.u_obj.cone;
	origin_to_vertex = vec3_norm(vec3_get_dir(*cone.vertex, ray.origin));
	theta = deg_to_rad(cone.angle / 2);
	abc[0] = powf(vec3_dot(ray.v_norm, *cone.v_norm), 2) - powf(cosf(theta), 2);
	abc[1] = 2 * ((vec3_dot(ray.v_norm, *cone.v_norm) * 
				vec3_dot(origin_to_vertex, *cone.v_norm)) 
			- vec3_dot(ray.v_norm, origin_to_vertex) * powf(cosf(theta), 2));
	abc[2] = powf(vec3_dot(origin_to_vertex, *cone.v_norm), 2) 
		- vec3_dot(origin_to_vertex, origin_to_vertex) * powf(cosf(theta), 2);
	d = (powf(abc[1], 2) - (4 * abc[0] * abc[2]));
	if (d < 0)
		return (false);
	else if (equal(d, 0))
	{
		t[0] = -abc[1] / (2 * abc[0]);
		t[1] = t[0];
	}
	else
	{
		t[0] = (-abc[1] + sqrtf(d)) / (2 * abc[0]);
		t[1] = (-abc[1] - sqrtf(d)) / (2 * abc[0]);
	}
	hit->p1 = vec3_get_pt(ray, t[0]);
	hit->p2 = vec3_get_pt(ray, t[1]);
	if (!vec3_pt_on_line(ray, hit->p1))
		hit->p1 = hit->p2;
	if ((!vec3_pt_on_line(ray, hit->p2)))
		return (false);
	return (true);
}
