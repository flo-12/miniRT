/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:13:02 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/22 20:04:44 by lwidmer          ###   ########.fr       */
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
t_exit_code	parse_sphere(char **split, t_sphere *sphere)
{
	if (ptr_len(split) != 4)
		return (INPUT_ERROR);
	sphere->center = ft_calloc(1, sizeof(t_coordinates));
	if (!sphere->center)
		return (MALLOC_ERROR);
	sphere->color = ft_calloc(1, sizeof(t_color));
	if (!sphere->color)
		return (MALLOC_ERROR);
	if (store_coordinates(split[1], -99, -99, sphere->center) != SUCCESS
		|| store_nbr_float(split[2], -99, -99, &sphere->d) != SUCCESS
		|| store_color(split[3], sphere->color) != SUCCESS)
		return (INPUT_ERROR);
	return (SUCCESS);
}

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
t_exit_code	parse_plane(char **split, t_plane *plane)
{
	if (ptr_len(split) != 4)
		return (INPUT_ERROR);
	plane->point = ft_calloc(1, sizeof(t_coordinates));
	if (!plane->point)
		return (MALLOC_ERROR);
	plane->v_norm = ft_calloc(1, sizeof(t_coordinates));
	if (!plane->v_norm)
		return (MALLOC_ERROR);
	plane->color = ft_calloc(1, sizeof(t_color));
	if (!plane->color)
		return (MALLOC_ERROR);
	if (store_coordinates(split[1], -99, -99, plane->point) != SUCCESS
		|| store_coordinates(split[2], -99, -99, plane->v_norm) != SUCCESS
		|| store_color(split[3], plane->color) != SUCCESS)
		return (INPUT_ERROR);
	*plane->v_norm = vec3_norm(*plane->v_norm);
	return (SUCCESS);
}

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
t_exit_code	parse_cylinder(char **split, t_cylinder *cylinder)
{
	if (ptr_len(split) != 6)
		return (INPUT_ERROR);
	cylinder->center = ft_calloc(1, sizeof(t_coordinates));
	if (!cylinder->center)
		return (MALLOC_ERROR);
	cylinder->v_norm = ft_calloc(1, sizeof(t_coordinates));
	if (!cylinder->v_norm)
		return (MALLOC_ERROR);
	cylinder->color = ft_calloc(1, sizeof(t_color));
	if (!cylinder->color)
		return (MALLOC_ERROR);
	if (store_coordinates(split[1], -99, -99, cylinder->center) != SUCCESS
		|| store_coordinates(split[2], -99, -99, cylinder->v_norm) != SUCCESS
		|| store_nbr_float(split[3], -99, -99, &cylinder->d) != SUCCESS
		|| store_nbr_float(split[4], -99, -99, &cylinder->h) != SUCCESS
		|| store_color(split[5], cylinder->color) != SUCCESS)
		return (INPUT_ERROR);
	*cylinder->v_norm = vec3_norm(*cylinder->v_norm);
	return (SUCCESS);
}

/* init_fct_ptr:
*	Initializes the function pointers.
*
*	Return: -
*/
void	init_fct_ptr(int id, t_object *obj)
{
	if (id == SPHERE)
	{
		obj->fct_free = &free_sphere;
		obj->fct_intersect = &intersect_sphere;
		obj->fct_color = &color_sphere;
	}
	else if (id == PLANE)
	{
		obj->fct_free = &free_plane;
		obj->fct_intersect = &intersect_plane;
		obj->fct_color = &color_plane;
	}
	else if (id == CYLINDER)
	{
		obj->fct_free = &free_cylinder;
		obj->fct_intersect = &intersect_cylinder;
		obj->fct_color = &color_cylinder;
	}
	else if (id == CONE)
	{
		obj->fct_free = NULL; //&free_cylinder;
		obj->fct_intersect = NULL; //&intersect_cylinder;
		obj->fct_color = NULL; //&color_cylinder;
	}
}

/* parse_object:
*	Create a new t_object of the right type (SPHERE, ...)
*	in which the values of split are stored. Add the new
*	object at the end of the linked-list of "objects".
*
*	Return: SUCCESS in case of success and
*		(MALLOC_/INPUT_)ERROR in case of failure.
*/
t_exit_code	parse_object(char **split, t_object **objects, int id)
{
	t_object	*obj;
	int			e;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (MALLOC_ERROR);
	obj->identifier = id;
	obj->next = NULL;
	e = 0;
	if (id == SPHERE)
		e = parse_sphere(split, &(obj->u_obj.sphere));
	else if (id == PLANE)
		e = parse_plane(split, &(obj->u_obj.plane));
	else if (id == CYLINDER)
		e = parse_cylinder(split, &(obj->u_obj.cylinder));
	else if (id == CONE)
		e = parse_cone(split, &(obj->u_obj.cone));
	init_fct_ptr(id, obj);
	ft_lstadd_back_obj(objects, obj);
	return (e);
}
