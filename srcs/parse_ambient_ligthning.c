/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_ligthning.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:29:09 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/02 10:29:11 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* parse_ambient_ligthning:
*
*/
int	parse_ambient_ligthning(char **split, t_ambient **ambient)
{
	if (*ambient)
		return (INPUT_ERROR);
	if (ptr_len(split) != 3)
		return (INPUT_ERROR);
	*ambient = malloc(sizeof(t_ambient));
	if (!(*ambient))
		return (MALLOC_ERROR);
	if (!store_nbr(split[1], 0, 1, &(*ambient)->ratio)
		|| !store_color(split[2], &(*ambient)->color))
		return (INPUT_ERROR);
	return (SUCCESS);
}
