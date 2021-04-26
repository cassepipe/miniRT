/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:27 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 10:38:45 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	parse_double(char **input)
{
	skip_blank_and_one_comma(input);
	return (parse_double_or_die(input));
}

/*
**  Here is a function to parse a double literal in a string.
** 	If parsing fails, it calls die() to abort the program;
**	It "advances" in the string by incrementing the pointer.
*/

double	parse_double_or_die(char **iput)
{
	char	*neg;
	double	ret;
	double	div;
	bool	dot;

	neg = NULL;
	ret = 0;
	div = 1;
	dot = false;
	if (**iput == '-')
		neg = (*iput)++;
	if (!ft_isdigit(**iput))
		die("Invalid data : Could not parse double literal");
	while (ft_isdigit(**iput) || (**iput == '.' && !dot))
	{
		if (**iput == '.')
			dot = true;
		else
		{
			div = dot ? div / 10 : div;
			ret = dot ? ret + (**iput - '0') * div : ret * 10 + (**iput - '0');
		}
		(*iput)++;
	}
	return (neg ? -ret : ret);
}

int		parse_int(char **input)
{
	skip_blank_and_one_comma(input);
	return (parse_int_or_die(input));
}

int		parse_int_or_die(char **input)
{
	char	*neg;
	int		ret;

	neg = NULL;
	ret = 0;
	if (**input == '-')
		neg = (*input)++;
	if (!ft_isdigit(**input))
		die("Invalid data : Could not parse integer literal");
	while (ft_isdigit(**input))
	{
		ret = ret * 10 + (**input - '0');
		(*input)++;
	}
	return (neg ? -ret : ret);
}
