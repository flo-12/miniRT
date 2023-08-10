/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:31:39 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/10 20:54:06 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
ipp = image plane point
*/

/*
to know whther or not the min distance should be updated we have to check 
whether the distance from this intersection for the current primary ray to the
camera viewpoint (vp) is closer than a prior one (if there has been any)
if so it returns true and updates the closest intersection for our render
primary_ray function
*/

/*
bool	check_p_hit(t_coordinates vp, t_hit p_hit, t_coordinates 
		*closest_intersect)
{
	static float	min_distance;
	float			distance_p1;
	float			distance_p2;

	distance_p1 = distance_points(vp, p_hit.p1);
	distance_p2 = distance_points(vp, p_hit.p2);
	if (min_distance == 0 || distance_p1 < min_distance || distance_p2 
		< min_distance)
	{
		if (distance_p1 <= distance_p2)
			*closest_intersect = p_hit.p1;
		else	
			*closest_intersect = p_hit.p2;
		return (true);
	}
	else
		return (false);
}

*/

void	print_vector(t_vector v)
{
	printf("origin:		x[%f]	y[%f]	z[%f]\n", v.origin.x, v.origin.y, v.origin.z);
	printf("direction:	x[%f]	y[%f]	z[%f]\n", v.v_norm.x, v.v_norm.y, v.v_norm.z);
}

void	print_point(t_coordinates p)
{
	printf("point:		x[%f]	y[%f]	z[%f]\n", p.x, p.y, p.z);
}

/*
give the primary ray, I check whether there is an intersection for each object
given the direction of the intersection and the distance of it I can update it
*/

void	render_primary_ray(t_global global, t_vector primary_ray, t_pixel pixel)
{
	t_object		*object;
	t_hit			p_hit;
	//t_coordinates	closest_intersect;
	t_object		*closest_object;

	object = global.objects;
	closest_object = NULL;
	while (object)
	{
		if (render_intersect(*object, primary_ray, &p_hit) == true)
		{
			/*
			if (check_p_hit(*global.camera->point, p_hit, 
				&closest_intersect))
				closest_object = object;
			*/
			//printf("hit at:!");
			//print_point(p_hit.p1);
			//printf("\n");
			closest_object = object;
		}
		object = object->next;
	}
	if (closest_object)
		mlx_put_pixel(&global.img, pixel.x, pixel.y, COLOR_WHITE);
}

t_coordinates	point(float x, float y, float z)
{
	t_coordinates	tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return (tmp);
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
	//float			cos_theta;
	//float			sin_theta;

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

void	print_camera_matrix(t_camera c)
{
	printf("forward:	x[%f]	y[%f]	z[%f]\n", c.m[2][0], c.m[2][1], c.m[2][2]);
	printf("right:		x[%f]	y[%f]	z[%f]\n", c.m[0][0], c.m[0][1], c.m[0][2]);
	printf("up:		x[%f]	y[%f]	z[%f]\n", c.m[1][0], c.m[1][1], c.m[1][2]);

}

t_exit_code	render_routine(t_global global)
{
	t_vector	primary_ray;
	t_pixel		pixel;


	//print_camera_matrix(*global.camera);
	//print_point(*global.camera->point);
	/*
	printf("\n");
	pixel.x = 0;
	pixel.y = 0;
	primary_ray = compute_primary_ray(*(global.camera), pixel);
	print_vector(primary_ray);
	*/
	/*
	printf("angle between rays is %f\n", 
			acosf(vec3_dot(primary_ray.v_norm, primary_ray2.v_norm) / 
				( fabs(vec3_dist_pts(primary_ray.origin, primary_ray.v_norm)) * 
				fabs(vec3_dist_pts(primary_ray2.origin, primary_ray2.v_norm)))));
	*/
	/*
	pixel.x = 899;
	pixel.y = 0;
	primary_ray2 = compute_primary_ray(*(global.camera), pixel);
	print_vector(primary_ray2);
	printf("angle is %f \n", acosf(vec3_dot(primary_ray.v_norm, primary_ray2.v_norm)));
	printf("\n");
	*/
	/*
	pixel.x = 899;
	pixel.y = 899;
	primary_ray2 = compute_primary_ray(*(global.camera), pixel);
	print_vector(primary_ray);
	printf("\n");
	pixel.x = 449;
	pixel.y = 449;
	primary_ray = compute_primary_ray(*(global.camera), pixel);
	*/
	//render_primary_ray(global, primary_ray, pixel);
	
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
