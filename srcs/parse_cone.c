/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:05:42 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/22 20:15:35 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_exit_code	parse_cone(char **split, t_cone *cone)
{
	if (ptr_len(split) != 5)
		return (INPUT_ERROR);
	cone->vertex = ft_calloc(1, sizeof(t_coordinates));
	if (!cone->vertex)
		return (MALLOC_ERROR);
	cone->v_norm = ft_calloc(1, sizeof(t_coordinates));
	if (!cone->v_norm)
		return (MALLOC_ERROR);
	cone->color = ft_calloc(1, sizeof(t_color));
	if (!cone->color)
		return (MALLOC_ERROR);
	if (store_coordinates(split[1], -99, -99, cone->vertex) != SUCCESS
		|| store_coordinates(split[2], -99, -99, cone->v_norm) != SUCCESS
		|| store_nbr_float(split[3], -99, -99, &cone->angle) != SUCCESS
		|| store_color(split[4], cone->color) != SUCCESS)
		return (INPUT_ERROR);
	*cone->v_norm = vec3_norm(*cone->v_norm);
	return (SUCCESS);
}
