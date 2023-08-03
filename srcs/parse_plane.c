/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:29:52 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/02 10:29:54 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* parse_plane:
*	Stores the values of each string in split in 
*	the structs. The format of split must be the 
*	following:
*		split[0] -> identifier 		=> not used
*		split[1] -> point in plane	=> plane->point
*		split[2] -> normalized vetor=> plane->v_norm
*		split[3] -> RGB colors		=> plane->color
*	The format of split is checked and also the
*	format of the numbers in the str and the amount
*	of numbers provided.
*
*	Return: SUCCESS in case of success and otherwise
*		the belonging error (INPUT_ERROR or MALLOC_ERROR).
*/
int	parse_plane(char **split, t_plane **plane)
{
	if (ptr_len(split) != 4)
		return (INPUT_ERROR);
	*plane = malloc(sizeof(t_plane));
	if (!(*plane))
		return (MALLOC_ERROR);
	(*plane)->point = malloc(sizeof(t_coordinates));
	if (!(*plane)->point)
		return (MALLOC_ERROR);
	(*plane)->v_norm = malloc(sizeof(t_coordinates));
	if (!(*plane)->v_norm)
		return (MALLOC_ERROR);
	(*plane)->color = malloc(sizeof(t_color));
	if (!(*plane)->color)
		return (MALLOC_ERROR);
	if (store_coordinates(split[1], -99, -99, &(*plane)->point) != SUCCESS
		|| store_coordinates(split[2], -1, 1, &(*plane)->v_norm) != SUCCESS
		|| store_color(split[3], &(*plane)->color) != SUCCESS)
		return (INPUT_ERROR);
	return (SUCCESS);
}
