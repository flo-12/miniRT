/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:33:11 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/16 13:22:25 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coordinates	camera_to_world(float m[3][3], t_coordinates v)
{
	t_coordinates	dir;

	dir.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0];
	dir.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1];
	dir.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2];
	return (dir);
}

void	calc_camera_matrix(t_camera *camera)
{
	t_coordinates	forward;
	t_coordinates	tmp;
	t_coordinates	right;
	t_coordinates	up;

	if (!equal(vec3_dot(point(0, 1, 0), *camera->v_norm), 1))
		tmp = point(0, 1, 0);
	else
		tmp = point(1, 0, 0);
	forward = vec3_norm(*camera->v_norm);
	right = vec3_cross(tmp, forward);
	up = vec3_cross(forward, right);
	camera->m[0][0] = right.x;
	camera->m[0][1] = right.y;
	camera->m[0][2] = right.z;
	camera->m[1][0] = up.x;
	camera->m[1][1] = up.y;
	camera->m[1][2] = up.z;
	camera->m[2][0] = forward.x;
	camera->m[2][1] = forward.y;
	camera->m[2][2] = forward.z;
}

void	calc_camera_scale(t_camera *camera)
{
	camera->scale = tanf(((camera->fov / 2) * M_PI) / 180);
}

void	calc_aspect_ratio(t_camera *camera)
{
	camera->aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
}
