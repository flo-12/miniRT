/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:34:27 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/11 12:52:15 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_camera_matrix(t_camera c)
{
	printf("forward:	x[%f]	y[%f]	z[%f]\n", c.m[2][0], c.m[2][1], c.m[2][2]);
	printf("right:		x[%f]	y[%f]	z[%f]\n", c.m[0][0], c.m[0][1], c.m[0][2]);
	printf("up:		x[%f]	y[%f]	z[%f]\n", c.m[1][0], c.m[1][1], c.m[1][2]);
}

void    print_image_plane_corners(t_global global)
{
    t_vector    left_upper;
    t_vector    right_upper;
    t_vector    left_lower;
    t_vector    right_lower;
    t_pixel     pixel;

    pixel.x = 0;
    pixel.y = 0;
    left_upper = compute_primary_ray(*(global.camera), pixel);
    printf("\033[31mleft upper\033[0m corner vector is:\n");
    print_vector(left_upper);
    printf("\n");

    pixel.x = 899;
    pixel.y = 0;
    right_upper = compute_primary_ray(*(global.camera), pixel);
    printf("\033[31mright upper\033[0m corner vector is:\n");
    print_vector(right_upper);
    printf("\n");

    pixel.x = 0;
    pixel.y = 899;
    left_lower = compute_primary_ray(*(global.camera), pixel);
    printf("\033[31mleft lower\033[0m corner vector is:\n");
    print_vector(left_lower);
    printf("\n");

    pixel.x = 899;
    pixel.y = 899;
    right_lower = compute_primary_ray(*(global.camera), pixel);
    printf("\033[31mright lower\033[0m corner vector is:\n");
    print_vector(right_lower);
    printf("\n");

    printf("angle between left and right upper: rad[%f]	deg[%f] \n",
        vec3_angle_rad(left_upper.v_norm, right_upper.v_norm),
        vec3_angle_deg(left_upper.v_norm, right_upper.v_norm));
}
