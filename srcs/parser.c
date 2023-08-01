/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:30 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/01 15:41:32 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* add_element:
*	Parses 
*/
bool	add_element(char **split, t_global *global)
{

}

/* split_line:
*	Gets a line of the input file and splits it by the
*	space (' ') as a delimiter into several strings.
*
*	Return: pointer to the split strings in case of 
*		success and NULL in case of error.
*/
char	**split_line(char *line_src)
{
	char	**split;
	char	*line;
	int		i;

	line = malloc(sizeof(char) * ft_strlen(line_src));
	if (!line)
		return (NULL);
	ft_strlcat(line, line_src, ft_strlen(line_src));
	split = ft_split(line, ' ');
	free(line);
	if (!split)
		return (NULL);
	return (split);
}

/* parser:
*
*/
int	parser(char *filename, t_global *global)
{
	int		fd;
	char	*line;
	char	**split;
	int		e;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		split = split_line(line);
		free(line);
		if (!split)
			return (2);
		e = add_element(split, global);
		free_ptr(split);
		if (e)
			return (e);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
