/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:05 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/01 15:41:08 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/**************************************************************************
*                               HEADERS                                   *
**************************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

# include <math.h>
# include "miniRT_define.h"
# include "libft.h"

/**************************************************************************
*                               FUNCTIONS                                 *
**************************************************************************/

// parser
int	parse(char *filename, t_global *global);
int	parse_light(char **split, t_light **light);
int	parse_camera(char **split, t_camera **camera);
int	parse_ambient_ligthing(char **split, t_ambient **ambient);
int	parse_object(char **split, t_object **objects, int id);
int	store_coordinates(char *str, float min, float max, t_coordinates *coordinates);
int	store_nbr_float(char *str, float min, float max, float *nbr);
int	store_color(char *str, t_color *color);

// utils.c
int	ptr_len(char **ptr);
void	free_ptr(char **ptr);

#endif
