/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:42:40 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/01 19:00:34 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_exit_code create_mlx(t_global **d)
{
	t_exit_code e;
	t_global	*data;
	
	e = SUCCESS;
	data->mlx = mlx_init();
	if (!data->mlx)
		e = MLX_ERROR;
	if (e == SUCCESS)
		data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!data->win)
		e = MLX_ERROR;
	if (e == SUCCESS)
		data.img.ptr = mlx_new_image(data-mlx. WIN_WIDTH, WIN_HEIGHT);
	if (!data.img.ptr)
		e = MLX_ERROR;
	if (e == SUCCESS)
		data.img.addr = mlx_get_data_addr(data.img.ptr, &data.img.bits_per_pixel, \
			&data.img.line_length, &data.img.endian);
	if (!data.img.addr)
		e = MLX_ERROR;
	return (e);
}


