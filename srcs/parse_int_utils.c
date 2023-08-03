/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:16:19 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/02 15:16:21 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* in_range_int:
*	Checks if the nbr is in the range of [min..max].
*
*	Return: true if in range and false if out of range.
*/
static bool	in_range_int(int nbr, int min, int max)
{
	if (nbr >= min && nbr <= max)
		return (true);
	else
		return (false);
}

/* valid_int:
*	Check if the str is in the correct format of an
*	int by checking if it consists only of numeric
*	values and a maximum of one minus at the
*	beginning (followed by numbers).
*
*	Return: true if str is in the format of a float and
*		otherwise false.
*/
static bool	valid_int(char *str)
{
	if (*str == '-')
	{
		str++;
		if (!(*str))
			return (false);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

/* store_nbr_int:
*	Check first if the str is a valid int. Secondly convert
*	the str to an int and store it in nbr. Check at the end
*	if int is in the range of min and max.
*
*	Return: SUCCESS (0) in case all checks are passed and 
*		otherwise INPUT_ERROR.
*/
static int	store_nbr_int(char *str, int min, int max, int *nbr)
{
	if (!valid_int(str))
		return (INPUT_ERROR);
	*nbr = ft_atoi(str);
	if (!in_range_int(*nbr, min, max))
		return (INPUT_ERROR);
	return (SUCCESS);
}

/* store_color:
*	Stores the three RGB-colors in str in the struct.
*	The colors in str must be seperated by ',' and
*	the string must contain the three RGB-values.
*	Each value must lie in the given range of [0..255]
*	and must be a valid int-value.
*
*	Return: SUCCESS (0) in case of success and INPUT_ERROR
*		otherwise (a check failed).
*/
int	store_color(char *str, t_color *color)
{
	char	*r;
	char	*g;
	char	*b;

	r = str;
	g = ft_strchr(r, ',');
	if (!g)
		return (INPUT_ERROR);
	*g = '\0';
	g++;
	b = ft_strchr(g, ',');
	if (!b)
		return (INPUT_ERROR);
	*b = '\0';
	b++;
	if (store_nbr_int(r, 0, 255, &color->r) != SUCCESS
		|| store_nbr_int(g, 0, 255, &color->g) != SUCCESS
		|| store_nbr_int(b, 0, 255, &color->b) != SUCCESS)
		return (INPUT_ERROR);
	return (SUCCESS);
}
