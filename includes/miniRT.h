/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:05 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/25 12:15:56 by fbecht           ###   ########.fr       */
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

// parse.c
t_exit_code		parse(char *filename, t_global *global);
// parse_light_ambient_camera.c
t_exit_code		parse_light(char **split, t_light **light);
t_exit_code		parse_camera(char **split, t_camera **camera);
t_exit_code		parse_ambient_ligthing(char **split, t_ambient **ambient);
// parse_object.c
t_exit_code		parse_object(char **split, t_object **objects, int id);
t_exit_code		parse_cone(char **split, t_cone *cone);
// parse_init_fct_ptr.c
void			init_fct_ptr(int id, t_object *obj);

// parse_float_utils.c
int				store_coordinates(char *str, float min, float max, 
					t_coordinates *coordinates);
int				store_nbr_float(char *str, float min, float max, float *nbr);
// parse_int_utils.c
int				store_color(char *str, t_color *color);

// render_routine.c
t_exit_code		render_routine(t_global global);
t_vector		compute_primary_ray(t_camera camera, t_pixel pixel);
void			calc_camera_matrix(t_camera *camera);

// fct_in_object.c
bool			fct_inside_sphere(t_object obj, t_coordinates p);
bool			fct_inside_plane(t_object obj, t_coordinates p);
bool			fct_inside_cylinder(t_object obj, t_coordinates p);
bool			fct_inside_cone(t_object obj, t_coordinates p);

// camera_utils.c
t_coordinates	camera_to_world(float m[3][3], t_coordinates v);
void			calc_camera_matrix(t_camera *camera);
void			calc_camera_scale(t_camera *camera);
void			calc_aspect_ratio(t_camera *camera);

// render_intersect.c
bool			intersect_sphere(t_object obj, t_vector ray, t_hit *hit);
bool			intersect_plane(t_object obj, t_vector ray, t_hit *hit);
bool			intersect_cylinder(t_object obj, t_vector ray, t_hit *hit);

// render_inter_cone.c
bool			intersect_cone(t_object obj, t_vector ray, t_hit *hit);

// render_inter_cyl_utils.c
int				tube_check_valid_points(t_vector ray, 
					float (*t)[2], t_cylinder cyl);
// render_light.c
t_color			render_light(t_object obj, t_global global, t_vector shadow, 
					t_coordinates p_hit);
t_color			get_intensity(float intensity, t_color c_obj, t_color c_light, 
					bool ambient);
// fct_surface_norm.c
t_coordinates	surface_norm_plane(t_object obj, t_vector shadow);
t_coordinates	surface_norm_sphere(t_object obj, t_vector shadow);
t_coordinates	surface_norm_cylinder(t_object obj, t_vector shadow);
t_coordinates	surface_norm_cone(t_object obj, t_vector shadow);

// exit_free.c
t_exit_code		exit_free(t_global *global, t_exit_code e);
void			free_if(void *ptr);

// exit_free_objects.c
t_object		*free_sphere(t_object *obj);
t_object		*free_plane(t_object *obj);
t_object		*free_cylinder(t_object *obj);
t_object		*free_cone(t_object *obj);
void			free_ptr(char **ptr);

// render_utils.c
t_coordinates	point(float x, float y, float z);
bool			check_occlusion(t_object obj, t_vector shadow, float dist);
bool			check_p_hit(t_coordinates vp, t_hit p_hit, t_coordinates 
					*closest_intersect, float *min_distance);

// color_utils.c
int				color_to_int(t_color color);
t_color			add_color(t_color c1, t_color c2);
t_color			color(int r, int g, int b);
// color_utils2.c
t_color			color_range(t_color color);
t_color			color_sphere(t_object obj);
t_color			color_plane(t_object obj);
t_color			color_cylinder(t_object obj);
t_color			color_cone(t_object obj);

// vec3_utils1.c
t_coordinates	vec3_get_dir(t_coordinates p1, t_coordinates p2);
t_coordinates	vec3_norm(t_coordinates v);
int				vec3_pt_on_line(t_vector v, t_coordinates p);
float			vec3_dist_pts(t_coordinates p1, t_coordinates p2);
t_coordinates	vec3_get_pt(t_vector v, float d);
// vec3_utils2.c
t_coordinates	vec3_add(t_coordinates p1, t_coordinates p2);
t_coordinates	vec3_sub(t_coordinates p1, t_coordinates p2);
float			vec3_dot(t_coordinates p1, t_coordinates p2);
t_coordinates	vec3_cross(t_coordinates p1, t_coordinates p2);
t_coordinates	vec3_multiply_const(t_coordinates p1, float nbr);
// vec3_utils3.c
float			vec3_angle_rad(t_coordinates v1, t_coordinates v2);
float			vec3_angle_deg(t_coordinates v1, t_coordinates v2);

// math_utils.c
bool			equal(float nbr, float comp);
float			minf(float n1, float n2);

// mlx_utils.c
void			mlx_put_pixel(t_img *img, int x, int y, int color);
t_exit_code		create_mlx(t_global *d);
void			free_mlx(t_global *global);

// utils.c
int				ptr_len(char **ptr);
float			rad_to_deg(float degree);
float			deg_to_rad(float rad);
t_object		init_obj_plane(t_coordinates *point, t_coordinates *v_norm, 
					t_color *color);
void			ft_lstadd_back_obj(t_object **objects, t_object *new);

// parser_test.c
void			print_parse(t_global *data, t_exit_code e);
// parser_test_obj.c
void			print_objects(t_object *objs, int e);
// render_test.c
void			print_image_plane_corners(t_global global);
void			print_camera_matrix(t_camera c);
// test_utils.c
void			print_color(t_color color);
void			print_coord(t_coordinates coord);
void			print_nbr(float p);
void			print_vector(t_vector vector);

#endif
