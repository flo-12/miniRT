/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:11:40 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/01 19:11:43 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* free_ptr:
*	Frees all strings ptr is pointing at and ptr otself.
*	ptr ends on a NULL-pointer.
*/
void	free_ptr(char **ptr)
{
	char	**tmp;

	tmp = ptr;
	if (!ptr)
		return ;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(tmp);
}

/* replace:
*	Searches for the first occurance of the char "search" in
*	"str" and replaces it by the char "repl". If "search"
*	is not found, nothing is done.
*	
*	Return: nothing.
*/
void	replace(char *str, char search, char repl)
{
	while (*str)
	{
		if (*str == search)
		{
			*str = repl;
			return ;
		}
	}
}
