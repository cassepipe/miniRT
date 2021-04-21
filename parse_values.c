/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:27 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/21 15:06:39 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	skip_blank(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}

void	skip_blank_and_one_comma(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
	if (**input == ',')
		(*input)++;
	while (ft_isspace(**input))
		(*input)++;
}

static int		is_in(char c, const char *set)
{
	while(*set)
	{
		if (*set == c)
		{
			return 1;
		}
		set++;
	}
	return 0;
}

void	skip_set(char **input, const char *set)
{
	while (**input)
	{
		if (!is_in(**input, set))
		{
			return;
		}
		(*input)++;
	}
}

/*
**  Here is a function to parse a double literal in a string.
** 	If parsing fails, it has to call die();
**	Another requirement is that it "advances" in
**	the string by incrementing the pointer.
*/

double parse_double_or_die(char **input)
{
	char	*neg;
	double	ret;
	double  div;
	bool	dot;

	neg = NULL;
	ret = 0;
	div = 1;
	dot = false;
	if (**input == '-')
		neg = (*input)++;
	if (!ft_isdigit(**input))
	{
		die("Invalid data : Could not parse double literal" );
	}
	while (ft_isdigit(**input) || (**input == '.' && !dot))
	{
		if (**input == '.')
			dot = true;
		else
		{
			div = dot ? div / 10 : div;
			ret = dot ? ret + (**input - '0') * div : ret * 10 + (**input - '0');
		}
		(*input)++;
	}
//	printf("RESULT is %f\n", neg ? -ret : ret);
	return (neg ? -ret : ret);
}

double	parse_double(char **input)
{
	skip_blank_and_one_comma(input);
	return(parse_double_or_die(input));
}

t_vec3	parse_vec(char **input)
{
	t_vec3 vector;

	vector.x = parse_double(input);
	vector.y = parse_double(input);
	vector.z = parse_double(input);

	return (vector);
}

int		parse_int(char**input)
{
	skip_blank_and_one_comma(input);
	return (parse_int_or_die(input));
}

t_color	parse_color(char **input)
{
	t_color color;

	color.red = parse_int(input);
	color.green = parse_int(input);
	color.blue = parse_int(input);

	if (	color.red < 0
		||	color.red > 255
		||	color.green < 0
		||	color.green > 255
		||	color.blue < 0
		||	color.blue > 255)
		die ("Color not in range");
	return (color);
}

int parse_int_or_die(char **input)
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
	//printf("RESULT is %i\n", neg ? -ret : ret);
	return (neg ? -ret : ret);
}
