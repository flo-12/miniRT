/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:38:05 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/25 18:38:59 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_sphere(t_sphere sphere)
{
	printf("Object Type: SPHERE\n");
	print_coord(*sphere.center);
	print_nbr(sphere.d);
	print_color(*sphere.color);
}

void	print_plane(t_plane plane)
{
	printf("Object Type: PLANE\n");
	print_coord(*plane.point);
	print_coord(*plane.v_norm);
	print_color(*plane.color);
}

void	print_cylinder(t_cylinder cyl)
{
	printf("Object Type: CYLINDER\n");
	print_coord(*cyl.center);
	print_coord(*cyl.v_norm);
	print_nbr(cyl.d);
	print_nbr(cyl.h);
	print_color(*cyl.color);
}

void	print_cone(t_cone cone)
{
	printf("Object Type: CONE\n");
	print_coord(*cone.vertex);
	print_coord(*cone.v_norm);
	print_nbr(cone.angle);
	print_color(*cone.color);
}

void	print_objects(t_object *objs, int e)
{
	printf("\n****** PRINT_OBJECTS ******\n");
	if (!objs)
		printf("No object initialized\n");
	while (objs)
	{
		if (objs->identifier == SPHERE)
			print_sphere(objs->u_obj.sphere);
		else if (objs->identifier == PLANE)
			print_plane(objs->u_obj.plane);
		else if (objs->identifier == CYLINDER)
			print_cylinder(objs->u_obj.cylinder);
		else if (objs->identifier == CONE)
			print_cone(objs->u_obj.cone);
		else
			printf("Wrong identifier (id=%d)\n", objs->identifier);
		objs = objs->next;
	}
	printf("exit code = %d\n", e);
}
