/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:37:51 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/09 17:37:53 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* equal:
*	Checks if two float numbers (nbr and comp) are equal,
*	whereas nbr lies in a range of comp+-THRESH_FLOAT.
*	This is done due to comparison / rounding problems
*	with floats.
*
*	Return: TRUE if the numbers are equal and FALSE
*		otherwise.
*/
bool	equal(float nbr, float comp)
{
	if (nbr > comp - THRESH_FLOAT && nbr < comp + THRESH_FLOAT)
		return (true);
	else
		return (false);
}

float	minf(float n1, float n2)
{
	if (n1 <= n2)
		return (n1);
	else
		return (n2);
}
