/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:34:19 by lwidmer           #+#    #+#             */
/*   Updated: 2023/08/18 12:35:14 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* free_if:
*	Frees the pointer if it exists.
*/
void	free_if(void *ptr)
{
	if (ptr)
		free(ptr);
}

/* print_exit:
*	Print the error message corresponding to the exit
*	codes in t_exit_code.
*/
void	print_exit(t_exit_code e)
{
	if (e)
	{
		printf("Error:");
		if (e == OPENFILE_ERROR)
			printf(MSG_OPENFILE_ERROR);
		else if (e == MLX_ERROR)
			printf(MSG_MLX_ERROR);
		else if (e == MALLOC_ERROR)
			printf(MSG_MALLOC_ERROR);
		if (e == INPUT_ERROR)
			printf(MSG_INPUT_ERROR);
		if (e == ARG_ERROR)
			printf(MSG_ARG_ERROR);
		if (e == INPUT_INCOMPLETE)
			printf(MSG_INPUT_INCOMPLETE);
		if (e == FILETYPE_ERROR)
			printf(MSG_FILETYPE_ERROR);
	}
}
