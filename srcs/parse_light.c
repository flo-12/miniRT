/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:29:30 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/02 10:29:32 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* parse_light:
*	Stores the values of each string in split in 
*	the structs. The format of split must be the 
*	following:
*		split[0] -> identifier 		=> not used
*		split[1] -> light point		=> light->point
*		split[2] -> light brightness=> light->brightness
*		split[3] -> RGB colors		=> light->color
*	The format of split is checked and also the
*	format of the numbers in the str and the amount
*	of numbers provided.
*
*	Return: SUCCESS in case of success and otherwise
*		the belonging error (INPUT_ERROR or MALLOC_ERROR).
*/
int	parse_light(char **split, t_light **light)
{
	if (ptr_len(split) != 4)
		return (INPUT_ERROR);
	*light = malloc(sizeof(t_light));
	if (!(*light))
		return (MALLOC_ERROR);
	(*light)->point = malloc(sizeof(t_coordinates));
	if (!(*light)->point)
		return (MALLOC_ERROR);
	(*light)->color = malloc(sizeof(t_color));
	if (!(*light)->color)
		return (MALLOC_ERROR);
	if (store_coordinates(split[1], -99, -99, &(*light)->point) != SUCCESS
		|| store_nbr_float(split[2], 0, 1, &(*light)->brightness) != SUCCESS
		|| store_color(split[3], &(*light)->color) != SUCCESS)
		return (INPUT_ERROR);
	return (SUCCESS);
}
