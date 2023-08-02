/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:30:14 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/02 10:30:16 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* in_range_float:
*	Checks if the nbr is in the range of [min..max].
*
*	Return: true if in range and false if out of range.
*/
static bool	in_range_float(float nbr, float min, float max)
{
	if (nbr >= min - THRESH_FLOAT && nbr <= max + THRESH_FLOAT)
		return (true);
	else
		return (false);
}

/* valid_float:
*	Check if the str is in the correct format of a
*	float by checking if it consists only of numeric
*	values, a maximum of one (decimal-)point and a
*	maximum of one minus at the beginning (followed by
*	numbers).
*	
*	Return: true if str is in the format of a float and
*		otherwise false.
*/
static bool	valid_float(char *str)
{
	bool	dec;

	dec = false;
	if (*str == '-')
	{
		str++;
		if (!(*str))
			return (false);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			if (*str == '.' && dec == false)
				dec = true;
			else
				return (false);
		}
		str++;
	}
	return (true);
}

/* str_to_float:
*	Converts a string to a float number.
*	Overflows are not handled and will lead to wrong output.
*
*	Return: the converted number as a float.
*/
static float	str_to_float(char *str)
{
	float	nbr;

	nbr = ft_atoi(str);
	str = ft_strchr(str, '.');
	if (str && *(str + 1))
	{
		if (nbr > 0)
			nbr += (float)ft_atoi(str + 1) / (float)pow(10, ft_strlen(str + 1));
		else
			nbr -= (float)ft_atoi(str + 1) / (float)pow(10, ft_strlen(str + 1));
	}
	return (nbr);
}

/* store_nbr_float:
*	Check first if the str is a valid float. Secondly convert
*	the str to a float and store it in nbr. Checks at the end
*	if float is in the range of min and max. If min and max
*	values are equal, it isn't checked if nbr is in range.
*
*	Return: SUCCESS (0) in case all checks are passed and 
*		otherwise INPUT_ERROR.
*/
int	store_nbr_float(char *str, float min, float max, float *nbr)
{
	if (!valid_float(str))
		return (INPUT_ERROR);
	*nbr = str_to_float(str);
	if (min != max && !in_range_float(*nbr, min, max))
		return (INPUT_ERROR);
	return (SUCCESS);
}

/* store_coordinates:
*	Stores the three coordinates in str in the struct.
*	The coordinates in str must be seperated by ',' and
*	the string must contain three coordinates (x,y,z).
*	Each value must be a valid float-value.
*
*	Return: SUCCESS (0) in case of success and INPUT_ERROR
*		otherwise (a check failed).
*/
int	store_coordinates(char *str, float min, float max, t_coordinates *coordinates)
{
	char	*x;
	char	*y;
	char	*z;

	x = str;
	y = ft_strchr(y, ',');
	if (!y)
		return (INPUT_ERROR);
	*y = '\0';
	y++;
	z = ft_strchr(y, ',');
	if (!z)
		return (INPUT_ERROR);
	*z = '\0';
	z++;
	if (store_nbr_float(x, min, max, &coordinates->x) != SUCCESS
		|| store_nbr_float(y, min, max, &coordinates->y) != SUCCESS
		|| store_nbr_float(z, min, max, &coordinates->z) != SUCCESS)
		return (INPUT_ERROR);
	return (SUCCESS);
}
