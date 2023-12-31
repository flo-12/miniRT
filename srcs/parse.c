/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:30 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/22 20:12:26 by lwidmer          ###   ########.fr       */
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
	char	*tmp;

	tmp = ft_strchr(line, '\n');
	if (tmp != NULL)
		*tmp = '\0';
	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	return (split);
}

/* exit_parse:
*	Closes the file, pointed to by fd and returns e.
*
*	Return: the exit-code e passed as argument.
*/
int	exit_parse(int fd, t_exit_code e)
{
	close (fd);
	return (e);
}

/* check_input_complete:
*	Checks if all the necessary elements/object
*	were given in the input file.
*
*	Return: true if all elements/objects are
*		present and false otherwise.
*/
t_exit_code	check_input_complete(t_global *global, int fd)
{
	if (!global->light || !global->camera
		|| !global->ambient)
		return (exit_parse(fd, INPUT_INCOMPLETE));
	else
		return (exit_parse(fd, SUCCESS));
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
t_exit_code	add_element(char **split, t_global *global)
{
	t_exit_code	e;

	e = 0;
	if (!(*split))
		return (e);
	if (!(*(split + 1)))
		e = INPUT_ERROR;
	else if (ft_strncmp(split[0], "A", 2) == 0)
		e = parse_ambient_ligthing(split, &global->ambient);
	else if (ft_strncmp(split[0], "C", 2) == 0)
		e = parse_camera(split, &global->camera);
	else if (ft_strncmp(split[0], "L", 2) == 0)
		e = parse_light(split, &global->light);
	else if (ft_strncmp(split[0], "sp", 3) == 0)
		e = parse_object(split, &global->objects, SPHERE);
	else if (ft_strncmp(split[0], "pl", 3) == 0)
		e = parse_object(split, &global->objects, PLANE);
	else if (ft_strncmp(split[0], "cy", 3) == 0)
		e = parse_object(split, &global->objects, CYLINDER);
	else if (ft_strncmp(split[0], "co", 3) == 0)
		e = parse_object(split, &global->objects, CONE);
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
*	Return: Exit-code and 0 in case of success.
*/
t_exit_code	parse(char *filename, t_global *global)
{
	int			fd;
	char		*line;
	char		**split;
	t_exit_code	e;

	if (!ft_strrchr(filename, '.') || ft_strncmp(ft_strrchr(filename, '.'), 
			".rt", 4) != 0)
		return (FILETYPE_ERROR);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (OPENFILE_ERROR);
	line = get_next_line(fd);
	while (line)
	{
		split = split_line(line);
		free(line);
		if (!split)
			return (exit_parse(fd, MALLOC_ERROR));
		e = add_element(split, global);
		free_ptr(split);
		if (e)
			return (exit_parse(fd, e));
		line = get_next_line(fd);
	}
	return (check_input_complete(global, fd));
}
