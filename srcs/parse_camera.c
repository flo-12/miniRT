/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:29:20 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/02 10:29:21 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* parse_camera:
*	Stores the values of each string in split in 
*	the structs. The format of split must be the 
*	following:
*		split[0] -> identifier 		=> not used
*		split[1] -> view point		=> camera->point
*		split[2] -> normalized vector => camera->v_norm
*		split[3] -> field-of-view	=> camera->fov
*	The format of split is checked and also the
*	format of the numbers in the str and the amount
*	of numbers provided.
*	It also has to be the first initialization b/c
*	only one camera is allowed.
*
*	Return: SUCCESS in case of success and otherwise
*		the belonging error (INPUT_ERROR or MALLOC_ERROR).
*/
int	parse_camera(char **split, t_camera **camera)
{
	if (*camera)
		return (INPUT_ERROR);
	if (ptr_len(split) != 4)
		return (INPUT_ERROR);
	*camera = malloc(sizeof(t_camera));
	if (!(*camera))
		return (MALLOC_ERROR);
	*camera->point = malloc(sizeof(t_coordinates));
	if (!(*camera)->point)
		return (MALLOC_ERROR);
	*camera->v_norm = malloc(sizeof(t_coordinates));
	if (!(*camera)->v_norm)
		return (MALLOC_ERROR);
	if (store_coordinates(split[1], -99, -99, &(*camera)->point) != SUCCESS
		|| store_coordinates(split[2], -1, 1, &(*camera)->v_norm != SUCCESS)
		|| store_nbr_float(split[3], 0, 180, &(*camera)->fov))
		return (INPUT_ERROR);
	return (SUCCESS);
}
