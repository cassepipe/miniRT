#include "minirt.h"

#define log(...) printf

static int	ft_isspace(const char c)
{
	if (c == ' '
	|| c == '\t'
	|| c == '\v'
	|| c == '\n'
	|| c == '\f'
	|| c == '\r')
		return (1);
	return (0);
}


/*
**  Mock function to pretend we are returnig an int
** 	and to free some stuff before exiting;
*/


int die()
{
	//free_some_stuff();
	exit(EXIT_FAILURE);
}

void	skip_blank(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}

/*
**  Here is a function to parse a double literal in a sting.
** 	If parsing fails, it has to call die();
**	Another requirement is that it "advances" in
**	the string by incrementing the pointer.
*/

double parse_double_or_die(char **input)
{
	char	*neg;
	double	result;
	double  div;
	bool	dot;

	neg = NULL;
	result = 0;
	div = 1;
	dot = false;
	skip_blank(input);
	if (**input == '-')
		neg = (*input)++;
	if (!ft_isdigit(**input))
		die();
	while (ft_isdigit(**input) || (**input == '.' && !dot))
	{
		if (**input == '.')
			dot = true;
		else
		{
			if (dot)
				div /= 10;
			result = !dot ? result * 10 + (**input - '0') : result + (**input - '0') * div;
		}
		(*input)++;
	}
	/*if (**input && (**input != ',' || ft_isspace(**input)))
		die();*/
	return (neg ? -result : result);
}

