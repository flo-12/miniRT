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
int	intersect_conic(t_cone cone, t_vector ray, t_hit *hit)
{
	float			abc[3];
	float			t[2];
	float			d;
	float			theta;
	t_coordinates	origin_to_vertex;

	origin_to_vertex = vec3_norm(vec3_get_dir(cone.vertex, ray.origin))
	theta = degree_to_rad(cone.angle / 2);
	abc[0] = expf(vec3_dot(ray.v_norm, cone.v_norm), 2) - (expf(cosf(theta), 2));
	abc[1] = 2 * ( (vec3_dot(ray.v_norm, cone.v_norm) * 
					vec3_dot(origin_to_vertex, cone.v_norm)) -
					vec3_dot(ray.v_norm, origin_to_vertex) * expf(cosf(theta), 2)
					);
	abc[2] = expf(vec3_dot(origin_to_vertex, cone.v_norm), 2) -
				vec3_dot(origin_to_vertex, origin_to_vertex) * expf(cosf(theta), 2);
	d = expf(abc[1], 2) - (4 * abc[0] * abc[2]);
	t[0] = (-abc[1] + d) / (2 * abc[0]);
    t[1] = (-abc[1] - d) / (2 * abc[0]);
	hit->p1 = vec3_get_pt(ray, t[0]);
	hit->p2 = vec3_get_pt(ray, t[1]);
}

/*
possible scenarios:
2 intersect conic
1 intersect conic
no intersection
*/
bool	render_cone(t_object obj, t_vector ray, t_hit *hit)
{
	t_cone	cone;
	int		nbr_inter_conic;
	t_hit	hit_plane;

	cone = obj.u_obj.cone;
	nbr_inter_conic = intersect_conic(cyl, ray, hit);
	if (nbr_inter_conic > 0)
		return (true);
	else
		return (false);
}
