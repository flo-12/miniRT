/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_inter_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:11:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/24 09:33:21 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*

theta is half the cones opening angle
*/

typedef struct s_solve {
	float	t1;
	float	t2;
	float	a;
	float	b;
	float	c;
	float	d1;
	float	d2;
	float	det;
}	t_solve;

bool	render_cone(t_object obj, t_vector ray, t_hit *hit)
{
	t_solve			s;
	t_coordinates	theta;
	t_coordinates	w;
	float			m;
	t_cone			cone;

	cone = obj.u_obj.cone;
	theta = vec3_norm(*cone.v_norm);
	m = powf(4 / 2, 2) / powf(10, 2);
	w = vec3_sub(ray.origin, *cone.vertex);
	s.d1 = vec3_dot(ray.v_norm, theta);
	s.d2 = vec3_dot(w, theta);
	s.a = powf(s.d1, 2);
	s.a = vec3_dot(ray.v_norm, ray.v_norm) - m * s.a - s.a;
	s.b = 2 * (vec3_dot(ray.v_norm, w) - m * s.d1 * s.d2 - s.d1 * s.d2);
	s.c = vec3_dot(w, w) - m * powf(s.d2, 2) - powf(s.d2, 2);
	s.det = powf(s.b, 2) - (4 * s.a * s.c);
	if (s.det < 0)
		return (false);
	s.det = sqrtf(s.det);
	s.t1 = (-s.b - s.det) / (2 * s.a);
	s.t2 = (-s.b + s.det) / (2 * s.a);
    hit->p1 = vec3_get_pt(ray, s.t1);
    hit->p2 = vec3_get_pt(ray, s.t2);
    return (true);
}



/*
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
	return (true);
}
*/
