/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:41:14 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/18 12:24:54 by lwidmer          ###   ########.fr       */
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
	if (equal(*min_distance, 0) 
		|| minf(distance_p1, distance_p2) + THRESH_FLOAT < *min_distance)
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

/*
checks if the shadow ray is occluded by any other objects until it has reached
the origin of the light source.

RETURN: bool; false -> no occlusion was found)
*/

bool	check_occlusion(t_object obj, t_vector shadow, float dist)
{
	t_hit	hit;
	float	dist_hits;
	float	dist_hits_abs;

	if ((obj.fct_intersect)(obj, shadow, &hit) == true)
	{
		dist_hits = minf(vec3_dist_pts(shadow.origin, hit.p1), 
				vec3_dist_pts(shadow.origin, hit.p2));
		dist_hits_abs = minf(fabs(vec3_dist_pts(shadow.origin, hit.p1)), 
				fabs(vec3_dist_pts(shadow.origin, hit.p2)));
		if (dist > dist_hits && dist_hits_abs > THRESH_FLOAT)
			return (false);
	}
	return (true);
}

t_coordinates	point(float x, float y, float z)
{
	t_coordinates	tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return (tmp);
}
