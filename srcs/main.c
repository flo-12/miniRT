/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:36 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/01 15:41:39 by fbecht           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	int			e;
	t_global	*global;

	if (argc != 2)
		return (USER_ERROR);
	e = initialize_global(&global);
	if (e != SUCCESS)
		return (e); 
	e = parse(argv[1], global);
	if (e != SUCCESS)
		return (e);
	return (EXIT_SUCCESS);
}
