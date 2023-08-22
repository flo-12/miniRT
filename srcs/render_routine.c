/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:31:39 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/18 12:28:20 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
	old check shadow ray occlusion conditions, to be safe
	if (object != obj_close && render_intersect(*object, shadow_ray, &hit) 
	== true 
	&& dist > minf(vec3_dist_pts(shadow_ray.origin, hit.p1), 
	vec3_dist_pts(shadow_ray.origin, hit.p2))
	&& minf(fabs(vec3_dist_pts(shadow_ray.origin, hit.p1)), 
	fabs(vec3_dist_pts(shadow_ray.origin, hit.p2))) > THRESH_FLOAT)
*/
void	render_shadow_ray(t_global g, t_object *obj_close, 
							t_coordinates hit, t_pixel p)
{
	t_vector	shadow;
	t_color		color;
	t_object	*object;
	float		dist;

	color = get_intensity(g.ambient->ratio, 
			obj_close->fct_color(*obj_close), *g.ambient->color, true);
	while (g.light)
	{
		shadow.origin = hit;
		shadow.v_norm = vec3_norm(vec3_get_dir(hit, *(g.light->point)));
		object = g.objects;
		while (object)
		{
			dist = vec3_dist_pts(shadow.origin, *g.light->point);
			if (object != obj_close && !check_occlusion(*object, shadow, dist))
				break ;
			object = object->next;
		}
		if (!object)
			color = add_color(color, render_light(*obj_close, g, shadow, hit));
		g.light = g.light->next;
	}
	mlx_put_pixel(&g.img, p.x, p.y, color_to_int(color_range(color)));
}

/*
give the primary ray, the intersections function is called to check whether
there is an intersection with any object in the scene. It looks through all the
objects in the scene, saving the hit point (p_hit) with the closest
intersection.

RETURN: void
*/
void	render_primary_ray(t_global global, t_vector primary_ray, t_pixel pixel)
{
	t_object		*object;
	t_hit			p_hit;
	t_coordinates	closest_intersect;
	t_object		*closest_object;
	float			min_distance;

	object = global.objects;
	closest_object = NULL;
	min_distance = 0;
	while (object)
	{
		if ((object->fct_intersect)(*object, primary_ray, &p_hit) == true)
		{
			if (check_p_hit(*global.camera->point, p_hit, 
					&closest_intersect, &min_distance))
				closest_object = object;
		}
		object = object->next;
	}
	if (closest_object)
		render_shadow_ray(global, closest_object, closest_intersect, pixel);
}

t_vector	compute_primary_ray(t_camera camera, t_pixel pixel)
{
	t_vector		primary_ray;	
	float			camera_x;
	float			camera_y;
	float			camera_z;

	camera_x = (2 * (pixel.x + 0.5) / WIN_WIDTH - 1) * camera.scale;
	camera_y = (1 - 2 * (pixel.y + 0.5) / WIN_HEIGHT) * 
		camera.scale / camera.aspect_ratio;
	camera_z = 1;
	primary_ray.origin = *camera.point;
	primary_ray.v_norm = vec3_norm(camera_to_world(camera.m, 
				point(camera_x, camera_y, camera_z)));
	return (primary_ray);
}

t_exit_code	render_routine(t_global global)
{
	t_vector	primary_ray;
	t_pixel		pixel;

	calc_camera_scale(global.camera);
	calc_camera_matrix(global.camera);
	calc_aspect_ratio(global.camera);
	if (DEBUG_RENDER)
	{
		print_camera_matrix(*global.camera);
		print_image_plane_corners(global);
	}
	pixel.y = 0;
	while (pixel.y < WIN_HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIN_WIDTH)
		{
			primary_ray = compute_primary_ray(*(global.camera), pixel);
			render_primary_ray(global, primary_ray, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
	printf("finished rendering primary rays\n");
	return (SUCCESS);
}
