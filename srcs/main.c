/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:36 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/11 11:39:35 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* initialize_global:
*	Initialize the global struct.
*
*	Return: exit code in case of error and
*		otherwise success.
*/
int	initialize_global(t_global **global)
{
	*global = malloc(sizeof(t_global));
	if (!(*global))
		return (MALLOC_ERROR);
	(*global)->light = NULL;
	(*global)->camera = NULL;
	(*global)->ambient = NULL;
	(*global)->objects = NULL;
	return (SUCCESS);
}

void	print_exit(t_exit_code e)
{
	if (e)
	{
		printf("Error:\n");
		if (e == OPENFILE_ERROR)
			printf("Cannot open file\n");
		if (e == INPUT_ERROR)
			printf("Incorrect formatting of arguments in file\n");
		if (e == ARG_ERROR)
			printf("Incorrect number of arguments\n");
		if (e == INPUT_INCOMPLETE)
			printf("One parameter for A, C & L required\n");
		if (e == FILETYPE_ERROR)
			printf("Wrong filetype, use *.rt\n");
	}
}

int	main(int argc, char **argv)
{
	int			e;
	t_global	*global;

	if (argc != 2)
		return (ARG_ERROR);
	e = initialize_global(&global);
	if (e != SUCCESS)
		return (e); 
	e = parse(argv[1], global);
	print_exit(e);
	if (e != SUCCESS)
		return (e);
	print_parse(global, e);
	if (e != SUCCESS)
		return (e);	
	e = create_mlx(global);
	printf("exit is %i",  e);
	calc_camera_matrix(global->camera);
	render_routine(*global);
	mlx_put_image_to_window(global->mlx, global->win, global->img.ptr, 0, 0);
	mlx_loop(global->mlx);
	free_mlx(global);
	return (EXIT_SUCCESS);
}
