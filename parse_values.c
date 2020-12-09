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

int		is_in(char c, const char *set)
{
	while(*set)
	{
		if (*set == c)
			return 1;
		set++;
	}
	return 0;
}

void	skip_set(char **input, const char *set)
{
	while (**input)
	{
		if (!is_in(**input, set))
			return;
		(*input)++;
	}
}

/*
**  Here is a function to parse a double literal in a string.
** 	If parsing fails, it has to call die();
**	Another requirement is that it "advances" in
**	the string by incrementing the pointer.
*/

double parse_double_or_die(char **data)
{
	char	*neg;
	double	ret;
	double  div;
	bool	dot;

	neg = NULL;
	ret = 0;
	div = 1;
	dot = false;
	if (**data == '-')
		neg = (*data)++;
	if (!ft_isdigit(**data))
		die();
	while (ft_isdigit(**data) || (**data == '.' && !dot))
	{
		if (**data == '.')
			dot = true;
		else
		{
			div = dot ? div / 10 : div;
			ret = dot ? ret + (**data - '0') * div : ret * 10 + (**data - '0');
		}
		(*data)++;
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
