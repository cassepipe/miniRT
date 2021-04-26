/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:28:07 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 17:28:37 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		skip_blank(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}

void		skip_blank_and_one_comma(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
	if (**input == ',')
		(*input)++;
	while (ft_isspace(**input))
		(*input)++;
}

static int	is_in(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

void		skip_set(char **input, const char *set)
{
	while (**input)
	{
		if (!is_in(**input, set))
		{
			return ;
		}
		(*input)++;
	}
}
