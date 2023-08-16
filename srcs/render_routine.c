/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:31:39 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/16 13:35:53 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
to know whther or not the min distance should be updated we have to check 
whether the distance from this intersection for the current primary ray to the
camera viewpoint (vp) is closer than a prior one (if there has been any)
if so it returns true and updates the closest intersection for our render
primary_ray function
*/
bool	check_p_hit(t_coordinates vp, t_hit p_hit, t_coordinates 
		*closest_intersect, float *min_distance)
{
	float			distance_p1;
	float			distance_p2;

	distance_p1 = vec3_dist_pts(vp, p_hit.p1);
	distance_p2 = vec3_dist_pts(vp, p_hit.p2);
	/* if (*min_distance == 0 || distance_p1 < *min_distance || distance_p2 
		< *min_distance) */
	if (equal(*min_distance, 0) || minf(distance_p1, distance_p2) + THRESH_FLOAT < *min_distance)
	{
		if (distance_p1 <= distance_p2)
		{
			*min_distance = distance_p1;
			*closest_intersect = p_hit.p1;
		}
		else
		{
			*min_distance = distance_p2;
			*closest_intersect = p_hit.p2;
		}
		return (true);
	}
	else
		return (false);
}

void	render_shadow_ray(t_global global, t_object *obj_close, 
							t_coordinates p_hit, t_pixel pixel)
{
	t_vector	shadow_ray;
	t_color		diffuse_color;
	t_object	*object;
	t_hit		hit;
	float		dist;

	diffuse_color = get_intensity(global.ambient->ratio, 
			get_obj_color(*obj_close), *global.ambient->color, true);
	while (global.light)
	{
		shadow_ray.origin = p_hit;
		shadow_ray.v_norm = vec3_norm(vec3_get_dir(p_hit, *(global.light->point)));
		object = global.objects;
		while (object)
		{
			dist = vec3_dist_pts(shadow_ray.origin, *global.light->point);
			if (object != obj_close && render_intersect(*object, shadow_ray, &hit) == true 
				&& dist > minf(vec3_dist_pts(shadow_ray.origin, hit.p1), vec3_dist_pts(shadow_ray.origin, hit.p2))
				&& minf(fabs(vec3_dist_pts(shadow_ray.origin, hit.p1)), fabs(vec3_dist_pts(shadow_ray.origin, hit.p2))) > THRESH_FLOAT)
				break ;
			object = object->next;
		}
		if (!object)
			diffuse_color = add_color(diffuse_color, 
					render_light(*obj_close, *global.light, shadow_ray));
		global.light = global.light->next;
	}
	mlx_put_pixel(&global.img, pixel.x, pixel.y, 
		color_to_int(color_range(diffuse_color)));
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
		if (render_intersect(*object, primary_ray, &p_hit) == true)
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
	camera_y = (1 - 2 * (pixel.y + 0.5) / WIN_HEIGHT) * camera.scale / camera.aspect_ratio;
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
