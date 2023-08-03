/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:30:00 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/02 10:30:03 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* parse_cylinder:
*	Stores the values of each string in split in 
*	the structs. The format of split must be the 
*	following:
*		split[0] -> identifier 		=> not used
*		split[1] -> center			=> cylinder->center
*		split[2] -> normalized vetor=> cylinder->v_norm
*		split[3] -> diameter		=> cylinder->d
*		split[4] -> height			=> cylinder->h
*		split[5] -> RGB colors		=> cylinder->color
*	The format of split is checked and also the
*	format of the numbers in the str and the amount
*	of numbers provided.
*
*	Return: SUCCESS in case of success and otherwise
*		the belonging error (INPUT_ERROR or MALLOC_ERROR).
*/
*/
int	parse_cylinder(char **split, t_cylinder **cylinder)
{
	if (ptr_len(split) != 6)
		return (INPUT_ERROR);
	*cylinder = malloc(sizeof(t_cylinder));
	if (!(*cylinder))
		return (MALLOC_ERROR);
	(*cylinder)->center = malloc(sizeof(t_coordinates));
	if (!(*cylinder)->center)
		return (MALLOC_ERROR);
	(*cylinder)->v_norm = malloc(sizeof(t_coordinates));
	if (!(*cylinder)->v_norm)
		return (MALLOC_ERROR);
	(*cylinder)->color = malloc(sizeof(t_color));
	if (!(*plcylinderane)->color)
		return (MALLOC_ERROR);
	if (store_coordinates(split[1], -99, -99, &(*cylinder)->center) != SUCCESS
		|| store_coordinates(split[2], -1, 1, &(*cylinder)->v_norm) != SUCCESS
		|| store_nbr_float(split[3], -99, -99, (*cylinder)->d) != SUCCESS
		|| store_nbr_float(split[4], -99, -99, (*cylinder)->h) != SUCCESS
		|| store_color(split[5], &(*cylinder)->color) != SUCCESS)
		return (INPUT_ERROR);
	return (SUCCESS);
}
