/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:29:41 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/02 10:29:44 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* parse_sphere:
*	Stores the values of each string in split in 
*	the structs. The format of split must be the 
*	following:
*		split[0] -> identifier 		=> not used
*		split[1] -> sphere center	=> sphere->center
*		split[2] -> diameter		=> sphere->d
*		split[3] -> RGB colors		=> sphere->color
*	The format of split is checked and also the
*	format of the numbers in the str and the amount
*	of numbers provided.
*
*	Return: SUCCESS in case of success and otherwise
*		the belonging error (INPUT_ERROR or MALLOC_ERROR).
*/
int	parse_sphere(char **split, t_sphere **sphere)
{
	if (ptr_len(split) != 4)
		return (INPUT_ERROR);
	*sphere = malloc(sizeof(t_sphere));
	if (!(*sphere))
		return (MALLOC_ERROR);
	(*sphere)->center = malloc(sizeof(t_coordinates));
	if (!(*sphere)->center)
		return (MALLOC_ERROR);
	(*sphere)->color = malloc(sizeof(t_color));
	if (!(*sphere)->color)
		return (MALLOC_ERROR);
	if (store_coordinates(split[1], -99, -99, &(*sphere)->center) != SUCCESS
		|| store_nbr_float(split[2], -99, -99, &(*sphere)->d) != SUCCESS
		|| store_color(split[3], &(*sphere)->color) != SUCCESS)
		return (INPUT_ERROR);
	return (SUCCESS);
}
