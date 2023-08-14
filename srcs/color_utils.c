/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:18:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/14 12:01:42 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	color_to_int(t_color c)
{
	int	color;

	color = (c.r << 16) | (c.g << 8) | c.b;
	return (color);
}

/* add_color:
*	Adds the RGB values of two colors
*	
*	Return: the calculated color.
*/
t_color	add_color(t_color c1, t_color c2)
{
	t_color	c_ret;

	c_ret.r = c1.r + c2.r;
	c_ret.g = c1.g + c2.g;
	c_ret.b = c1.b + c2.b;
	return (c_ret);
}

t_color	color(int r, int g, int b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color	color_range(t_color color)
{
	if (color.b > 255)
		color.b = 255;
	if (color.g > 255)
		color.g = 255;
	if (color.r > 255)
		color.r = 255;
	return (color);
}
