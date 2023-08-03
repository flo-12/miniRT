/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:13:02 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/03 11:13:04 by fbecht           ###   ########.fr       */
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
int	parse_sphere(char **split, t_sphere *sphere)
{
	if (ptr_len(split) != 4)
		return (INPUT_ERROR);
	/* *sphere = malloc(sizeof(t_sphere));
	if (!(*sphere))
		return (MALLOC_ERROR); */
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

/* ft_lstadd_back_obj:
*	Add the new t_object "new" at the end of the
*	linked-list "objects".
*
*	Return: nothing.
*/
void	ft_lstadd_back_obj(t_object **objects, t_object *new)
{
	if (!objects || !new)
		return ;
	if (*objects)
	{
		while ((*objects)->next)
			(*objects) = (*objects)->next;
		(*objects)->next = new;
	}
	else
		*objects = new;
}

/* parse_object:
*	Create a new t_object of the right type (SPHERE, ...)
*	in which the values of split are stored. Add the new
*	object at the end of the linked-list of "objects".
*
*	Return: SUCCESS in case of success and
*		(MALLOC_/INPUT_)ERROR in case of failure.
*/
int	parse_object(char **split, t_object **objects, int id)
{
	t_object	*obj;
	int			e;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (MALLOC_ERROR);
	obj->identifier = id;
	obj->next = NULL;
	if (id == SPHERE)
		e = parse_sphere(split, &(obj->u_obj.sphere));
	// else if(id == PLANE)
	//		...
	ft_lstadd_back_obj(objects, obj);
	return (e);
}
