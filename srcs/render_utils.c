/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:41:14 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/14 12:41:49 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	color(int r, int g, int b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_coordinates	point(float x, float y, float z)
{
	t_coordinates	tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return (tmp);
}
