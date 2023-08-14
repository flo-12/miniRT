/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:31:39 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/14 18:35:09 by lwidmer          ###   ########.fr       */
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
	if (*min_distance == 0 || distance_p1 < *min_distance || distance_p2 
		< *min_distance)
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
	//t_color		ambient_color;
	t_color		diffuse_color;
	int			final_color;
	t_object	*object;
	t_hit		dummy;

	diffuse_color = get_intensity(global.ambient->ratio, 
		get_obj_color(*obj_close), *global.ambient->color); // check colored ambient light without bonus
	while (global.light)
	{
		shadow_ray.origin = p_hit;
		shadow_ray.v_norm = vec3_norm(vec3_get_dir(p_hit, *(global.light->point)));
		object = global.objects;
		while (object)
		{
			if (object != obj_close && render_intersect(*object, shadow_ray, &dummy) == true)
				break;
			object = object->next;
		}
		// check if first all intensities and RGB-colors of light should be summed up and at the end it's multiuplied with the obj_close color???
		if (!object)
			diffuse_color = add_color(diffuse_color, 
				 render_light(*obj_close, *global.light, shadow_ray));
		/* diffuse_color = diffuse_color +
			render_light(obj_close, global.light, shadow_ray); */
		global.light = global.light->next;
	}
	diffuse_color = color_range(diffuse_color);
	if (pixel.x < 1024 / 2 + 35 && pixel.x > 1024 / 2 + 25 && pixel.y == WIN_HEIGHT / 2)
			printf("color=(%d,%d,%d), v_norm=(%f,%f,%f)\n", 
				diffuse_color.r, diffuse_color.g, diffuse_color.b,
				shadow_ray.v_norm.x, shadow_ray.v_norm.y, shadow_ray.v_norm.z);
	final_color = color_to_int(diffuse_color);
	//final_color = color_to_int(*(global.ambient->color));
	//ambient_color = mul_color(*(global.ambient->color), global.ambient.ratio);
	//final_color = add_color(ambient_color, diffuse_color);
	mlx_put_pixel(&global.img, pixel.x, pixel.y, final_color);
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
	//int				color;

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
	{
		render_shadow_ray(global, closest_object, closest_intersect, pixel);
		/*
		if (closest_object->identifier == SPHERE)
			color = color_to_int(*closest_object->u_obj.sphere.color);
		if (closest_object->identifier == CYLINDER)
			color = color_to_int(*closest_object->u_obj.cylinder.color);
		if (closest_object->identifier == PLANE)
			color = color_to_int(*closest_object->u_obj.plane.color);
		mlx_put_pixel(&global.img, pixel.x, pixel.y, color);
		*/
	}
}

t_coordinates camera_to_world(float m[3][3], t_coordinates v)
{
	t_coordinates	dir;

	dir.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0];
	dir.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1];
	dir.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2];
	return (dir);
}

t_vector compute_primary_ray(t_camera camera, t_pixel pixel)
{
	t_vector		primary_ray;	
	float			camera_x;
	float			camera_y;
	float			camera_z;
	float			scale;

	scale = tanf(((camera.fov / 2) * M_PI) / 180);
	camera_x = (2 * (pixel.x + 0.5) / WIN_WIDTH - 1) * scale;
	camera_y = (1 - 2 * (pixel.y + 0.5) / WIN_HEIGHT) * scale;
	camera_z = 1;
	//print_point(point(camera_x, camera_y, camera_z));
	primary_ray.origin = *camera.point;
	//primary_ray.v_norm = vec3_norm(point(camera_x, camera_y, camera_z));
	primary_ray.v_norm = vec3_norm(camera_to_world(camera.m, 
							point(camera_x, camera_y, camera_z)));
	return (primary_ray);
}

void	calc_camera_matrix(t_camera *camera)
{
	t_coordinates	forward;
	t_coordinates	tmp;
	t_coordinates	right;
	t_coordinates	up;

	tmp = point(0, 1, 0);
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
	printf("dot_product %f\n", vec3_dot(forward, right));
	printf("dot_product %f\n", vec3_dot(forward, up));
}

t_exit_code	render_routine(t_global global)
{
	t_vector	primary_ray;
	t_pixel		pixel;

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
