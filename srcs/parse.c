/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:30 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/01 15:41:32 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* split_line:
*	Gets a line of the input file and splits it by the
*	space (' ') as a delimiter into several strings.
*	Also reaplces the newline ('\n') by a NUL ('\0').
*
*	Return: pointer to the split strings in case of 
*		success and NULL in case of error.
*/
char	**split_line(char *line)
{
	char	**split;
	
	replace(line, '\n', '\0');
	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	return (split);
}

/* add_element:
*	Checks the first string in split for the identifier
*	and calls the belonging function to create the 
*	object/element in global.
*	
*	Return: error-code in case of failure (differentiated)
*		by malloc and syntax error) and 0 in case of
*		success.
*/
int	add_element(char **split, t_global *global)
{
	int	e;

	e = 0;
	if (!(split + 1))
		e = INPUT_ERROR;
	else if (ft_strncmp(split[0], "A", 2) != 0)
		e = parse_ambient_ligthning(split, &global->ambient);
	else if (ft_strncmp(split[0], "C", 2) != 0)
		e = parse_camera(split, &global->camera);
	else if (ft_strncmp(split[0], "L", 2) != 0)
		e = parse_light(split, &global->light);
	else if (ft_strncmp(split[0], "sp", 3) != 0)
		e = parse_sphere(split, &global->objects);
	else if (ft_strncmp(split[0], "pl", 3) != 0)
		e = parse_plane(split, &global->objects);
	else if (ft_strncmp(split[0], "cy", 3) != 0)
		e = parse_cylinder(split, &global->objects);
	else
		e = INPUT_ERROR;
	return (e);
}

/* parse:
*	Reads the input file line by line, splits each line
*	by spaces and stores the value in the belonging
*	(depending on the identifier) struct.
*	Checks at the end if all mandatory elements were in 
*	the file (camera, ambient light, etc.)
*	Stops if an error in the input occurs (e.g. str when
*	number is expected or wrong identifier).
*
*	Return: Error-code and 0 in case of success.
*/
int	parse(char *filename, t_global *global)
{
	int		fd;
	char	*line;
	char	**split;
	int		e;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (OPENFILE_ERROR);
	line = get_next_line(fd);
	while (line)
	{
		split = split_line(line);
		free(line);
		if (!split)
			return (MALLOC_ERROR);
		e = add_element(split, global);
		free_ptr(split);
		if (e)
			return (e);	// (1) error: malloc fail | (2) error: wrong input in file
		line = get_next_line(fd);
	}
	close(fd);
	if (!check_input_complete(global))
		return (3);	// error: input not complete
	return (0);
}
