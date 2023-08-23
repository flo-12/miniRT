/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:36 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/22 20:21:21 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* initialize_global:
*	Initialize the global struct.
*
*	Return: exit code in case of error and
*		otherwise success.
*/
t_exit_code	initialize_global(t_global **global)
{
	*global = ft_calloc(1, sizeof(t_global));
	if (!(*global))
		return (MALLOC_ERROR);
	(*global)->light = NULL;
	(*global)->camera = NULL;
	(*global)->ambient = NULL;
	(*global)->objects = NULL;
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	int			e;
	t_global	*global;

	global = NULL;
	if (argc != 2)
		return (exit_free(global, ARG_ERROR));
	e = initialize_global(&global);
	if (e != SUCCESS)
		return (exit_free(global, e));
	e = parse(argv[1], global);
	if (e != SUCCESS)
		return (exit_free(global, e));
	if (DEBUG_PARSER)
		print_parse(global, e);
	if (e != SUCCESS)
		return (exit_free(global, e));
	e = create_mlx(global);
	if (!e)
	{
		render_routine(*global);
		mlx_put_image_to_window(global->mlx, global->win, global->img.ptr, 
			0, 0);
		mlx_loop(global->mlx);
	}
	return (exit_free(global, e));
}
