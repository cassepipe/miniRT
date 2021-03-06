/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 10:53:16 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 10:53:18 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	parse_color(char **input)
{
	t_color color;

	color.red = parse_int(input);
	color.green = parse_int(input);
	color.blue = parse_int(input);
	if (color.red < 0
		|| color.red > 255
		|| color.green < 0
		|| color.green > 255
		|| color.blue < 0
		|| color.blue > 255)
		die("Color not in range");
	return (color);
}
