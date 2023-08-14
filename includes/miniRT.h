/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:05 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/14 12:43:10 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/**************************************************************************
*                               HEADERS                                   *
**************************************************************************/

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "miniRT_define.h"
# include "libft.h"
# include "mlx.h"

/**************************************************************************
*                               FUNCTIONS                                 *
**************************************************************************/

// parser
t_exit_code		parse(char *filename, t_global *global);
t_exit_code		parse_light(char **split, t_light **light);
t_exit_code		parse_camera(char **split, t_camera **camera);
t_exit_code		parse_ambient_ligthing(char **split, t_ambient **ambient);
t_exit_code		parse_object(char **split, t_object **objects, int id);
int		store_coordinates(char *str, float min, float max, 
			t_coordinates *coordinates);
int		store_nbr_float(char *str, float min, float max, float *nbr);
int		store_color(char *str, t_color *color);

void    print_parse(t_global *data, t_exit_code e);

// utils.c
int				ptr_len(char **ptr);
void			free_ptr(char **ptr);

// test_utils.c
void    print_color(t_color color);
void    print_coord(t_coordinates coord);
void    print_nbr(float p);
void    print_vector(t_vector vector);

// render
void			calc_camera_matrix(t_camera *camera);

// render_test.c
void    	print_image_plane_corners(t_global global);
void    	print_camera_matrix(t_camera c);
// mlx_utils.c
void		mlx_put_pixel(t_img *img, int x, int y, int color);
t_exit_code create_mlx(t_global *d);
void    	free_mlx(t_global *global);

// render_routine.c
t_exit_code 	render_routine (t_global global);
t_vector		compute_primary_ray (t_camera camera, t_pixel pixel);
void			render_shadow_ray(t_global global, t_object obj_close, 
					t_coordinates pHit, t_pixel pixel);

// render_light.c
t_color			get_obj_color(t_object obj);
t_color			get_intensity(float intensity, t_color c_obj, t_color c_light);
t_color			render_light(t_object obj, t_light light, t_vector shadow);

// HELPER
t_coordinates	vec3_get_dir(t_coordinates p1, t_coordinates p2);
t_coordinates	vec3_norm(t_coordinates v);
int				vec3_pt_on_line(t_vector v, t_coordinates p);
float			vec3_dist_pts(t_coordinates p1, t_coordinates p2);
t_coordinates	vec3_get_pt(t_vector v, float d);
t_coordinates	vec3_cross(t_coordinates p1, t_coordinates p2);
t_coordinates	vec3_multiply_const(t_coordinates p1, float nbr);
t_coordinates	vec3_add(t_coordinates p1, t_coordinates p2);
t_coordinates	vec3_sub(t_coordinates p1, t_coordinates p2);
float			vec3_dot(t_coordinates p1, t_coordinates p2);
float   vec3_angle_rad(t_coordinates v1, t_coordinates v2);
float   vec3_angle_deg(t_coordinates v1, t_coordinates v2);


// color_utils.c
int color_to_int(t_color color);

// render_utils.c
t_color color(int r, int g, int b);
t_coordinates   point(float x, float y, float z);

bool			equal(float nbr, float comp);

// INTERSECT
bool			render_intersect(t_object obj, t_vector ray, t_hit *hit);
int				tube_check_valid_points(t_vector ray, float (*t)[2], t_cylinder cyl);

// COLOR (not mandatory)
// ...

// Exit and Print error code
t_exit_code		exit_free(t_global *global, t_exit_code e);

#endif
