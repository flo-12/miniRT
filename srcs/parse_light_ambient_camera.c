/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_ambient_camera.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:43:30 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/03 14:43:32 by fbecht           ###   ########.fr       */
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
	if (store_coordinates(split[1], -99, -99, (*light)->point) != SUCCESS
		|| store_nbr_float(split[2], 0, 1, &(*light)->brightness) != SUCCESS
		|| store_color(split[3], (*light)->color) != SUCCESS)
		return (INPUT_ERROR);
	return (SUCCESS);
}

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
	if (store_nbr_float(split[1], -1, 1, &(*ambient)->ratio) != SUCCESS
		|| store_color(split[2], (*ambient)->color) != SUCCESS)
		return (INPUT_ERROR);
	return (SUCCESS);
}

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
	(*camera)->point = malloc(sizeof(t_coordinates));
	if (!(*camera)->point)
		return (MALLOC_ERROR);
	(*camera)->v_norm = malloc(sizeof(t_coordinates));
	if (!(*camera)->v_norm)
		return (MALLOC_ERROR);
	if (store_coordinates(split[1], -99, -99, (*camera)->point) != SUCCESS
		|| store_coordinates(split[2], -1, 1, (*camera)->v_norm) != SUCCESS
		|| store_nbr_float(split[3], 1, 179, &(*camera)->fov) != SUCCESS)
		return (INPUT_ERROR);
	(*camera)->focal_len = (0.5 * WIN_WIDTH) / tanf((*camera)->fov / 2);
	return (SUCCESS);
}
