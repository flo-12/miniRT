/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_ligthing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:29:09 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/02 10:29:11 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* parse_ambient_ligthing:
*	Stores the values of each string in split in
*	the structs. The format of split must be the
*	following:
*		split[0] -> identifier 		=> not used
*		split[1] -> lighting ratio 	=> ambient->ratio
*		split[2] -> RGB-colors		=> ambient->color
*	The format of split is checked and also the
*	format of the numbers in the str and the amount
*	of numbers provided.
*	It also has to be the first initialization b/c
*	only one ambient lighting is allowed.
*
*	Return: SUCCESS in case of success and otherwise
*		the belonging error (INPUT_ERROR or MALLOC_ERROR).
*/
int	parse_ambient_ligthing(char **split, t_ambient **ambient)
{
	if (*ambient)
		return (INPUT_ERROR);
	if (ptr_len(split) != 3)
		return (INPUT_ERROR);
	*ambient = malloc(sizeof(t_ambient));
	if (!(*ambient))
		return (MALLOC_ERROR);
	(*ambient)->color = malloc(sizeof(t_color));
	if (!(*ambient)->color)
		return (MALLOC_ERROR);
	if (store_nbr(split[1], -1, 1, &(*ambient)->ratio) != SUCCESS
		|| store_color(split[2], &(*ambient)->color) != SUCCESS)
		return (INPUT_ERROR);
	return (SUCCESS);
}
