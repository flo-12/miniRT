/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:05 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/03 15:48:47 by lwidmer          ###   ########.fr       */
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

/**************************************************************************
*                               FUNCTIONS                                 *
**************************************************************************/

// parser
int		parse(char *filename, t_global *global);
int		parse_light(char **split, t_light **light);
int		parse_camera(char **split, t_camera **camera);
int		parse_ambient_ligthing(char **split, t_ambient **ambient);
int		parse_object(char **split, t_object **objects, int id);
int		store_coordinates(char *str, float min, float max, 
			t_coordinates *coordinates);
int		store_nbr_float(char *str, float min, float max, float *nbr);
int		store_color(char *str, t_color *color);

void    print_parse(t_global *data, t_exit_code e);

// utils.c
int		ptr_len(char **ptr);
void	free_ptr(char **ptr);

// render

// BIG
t_exit_code render_routine (t_global global);
t_vector	compute_primary_ray (t_global global, t_pixel pixel);

// SHADOW RAY (not mandatory)
void	render_shadow_ray(t_global global, t_object obj_close, t_coordinates pHit, t_pixel pixel);

// HELPER
t_coordinates	vector_normalize(t_coordinates direction);
float			vector_dot_product(t_coordinates p1, t_coordinates p2);
float			distance_points(t_coordinates p1, t_coordinates p2);
t_coordinates	get_vector_direction(t_coordinates p1, t_coordinates p2);

// INTERSECT
t_hit	intersect(t_obj obj, t_vector ray);
	// calls intersect_sphere, intersect_plane, intersect_cylinder

// COLOR (not mandatory)
// ...

#endif
