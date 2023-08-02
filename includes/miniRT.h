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

// parser.c
int	store_coordinates(char *str, t_coordinates *coordinates);
int	store_nbr_float(char *str, float min, float max, float *nbr);
int	store_color(char *str, t_color *color);

#endif
