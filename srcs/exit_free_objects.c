/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:53:57 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/15 11:53:59 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* free_sphere:
*	Frees the content of t_sphere and the object
*	itself.
*
*	Return: next object in the linked-list.
*/
t_object	*free_sphere(t_object *obj)
{
	t_object	*tmp;

	free_if((void *)obj->u_obj.sphere.center);
	free_if((void *)obj->u_obj.sphere.color);
	tmp = obj;
	obj = obj->next;
	free(tmp);
	return (obj);
}

/* free_plane:
*	Frees the content of t_plane and the object
*	itself.
*
*	Return: next object in the linked-list.
*/
t_object	*free_plane(t_object *obj)
{
	t_object	*tmp;

	free_if((void *)obj->u_obj.plane.point);
	free_if((void *)obj->u_obj.plane.v_norm);
	free_if((void *)obj->u_obj.plane.color);
	tmp = obj;
	obj = obj->next;
	free(tmp);
	return (obj);
}

/* free_cylinder:
*	Frees the content of t_cylinder and the object
*	itself.
*
*	Return: next object in the linked-list.
*/
t_object	*free_cylinder(t_object *obj)
{
	t_object	*tmp;

	free_if((void *)obj->u_obj.cylinder.center);
	free_if((void *)obj->u_obj.cylinder.v_norm);
	free_if((void *)obj->u_obj.cylinder.color);
	tmp = obj;
	obj = obj->next;
	free(tmp);
	return (obj);
}
