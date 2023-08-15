/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:42:40 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/11 11:44:45 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	cross_handler(t_global *global)
{
	mlx_loop_end(global->mlx);
	return (1);
}

int	keypress_handler(int keycode, t_global *vars)
{
	if (keycode == 65307)
		mlx_loop_end(vars->mlx);
	return (0);
}

void	mlx_put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (img->size_line * y + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	free_mlx(t_global *global)
{
	if (global->mlx)
	{
		if (global->win)
			mlx_destroy_window(global->mlx, global->win);
		if (global->img.ptr)
			mlx_destroy_image(global->mlx, global->img.ptr);
		mlx_destroy_display(global->mlx);
	}
}

t_exit_code	create_mlx(t_global *data)
{
	t_exit_code	e;

	e = SUCCESS;
	data->mlx = mlx_init();
	if (!data->mlx)
		e = MLX_ERROR;
	if (e == SUCCESS)
		data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!data->win)
		e = MLX_ERROR;
	if (e == SUCCESS)
		data->img.ptr = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.ptr)
		e = MLX_ERROR;
	if (e == SUCCESS)
		data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp, \
			&data->img.size_line, &data->img.endian);
	if (!data->img.addr)
		e = MLX_ERROR;
	mlx_hook(data->win, 2, 1L << 0, keypress_handler, data);
	mlx_hook(data->win, 17, 1L << 2, cross_handler, data);
	return (e);
}
