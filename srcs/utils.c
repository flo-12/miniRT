/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:11:40 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/01 19:11:43 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* ptr_len:
*	Calculates the length of the pointer.
*
*	Return: length of the pointer.
*/
int	ptr_len(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

/* rad_to_deg:
*	Conert angle from radians to degree.
*/
float	rad_to_deg(float degree)
{
	return (degree / M_PI * 180);
}

/* deg_to_rad:
*	Conert angle from degree to radians.
*/
float	deg_to_rad(float rad)
{
	return (rad * M_PI / 180);
}

/* init_obj_plane:
*	Initializes a t_object with a u_obj of a sphere,
*	which has the values passed as arguments.
*
*	Return: the new t_object.
*/
t_object	init_obj_plane(t_coordinates *point, 
	t_coordinates *v_norm, t_color *color)
{
	t_object	obj;

	obj.u_obj.plane = (t_plane){point, v_norm, color};
	return (obj);
}

/* ft_lstadd_back_obj:
*	Add the new t_object "new" at the end of the
*	linked-list "objects".
*
*	Return: nothing.
*/
void	ft_lstadd_back_obj(t_object **objects, t_object *new)
{
	t_object	*tmp;

	if (!objects || !new)
		return ;
	if (*objects)
	{
		tmp = *objects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*objects = new;
}
