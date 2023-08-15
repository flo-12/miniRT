/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:53:25 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/11 11:56:35 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_color(t_color color)
{
	printf("[COLOR] r=%d | g=%d | b=%d\n", 
		color.r, color.g, color.b);
}

void	print_coord(t_coordinates coord)
{
	printf("[COORDINATES] x=%f | y=%f | z=%f\n", 
		coord.x, coord.y, coord.z);
}

void	print_vector(t_vector vector)
{
	printf("origin:");
	print_coord(vector.origin);
	printf("direction:");
	print_coord(vector.v_norm);
}

void	print_nbr(float p)
{
	printf("[NBR] p=%f\n", p);
}
