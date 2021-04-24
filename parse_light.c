/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:08:10 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 14:33:07 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambl(char **input)
{
	ft_printf("Parsing ambient light...\n");
	if (!g_env.unique_amb)
		die("Two ambient lights defined. Only one is allowed");
	skip_blank(input);
	g_env.ambl_intensity = parse_double(input);
	if (g_env.ambl_intensity < 0
		|| g_env.ambl_intensity > 1)
		die("Ambient light intensity not in range [0,1]");
	g_env.ambl_color = parse_color(input);
	g_env.ambl_distrib = distribute_colors(g_env.ambl_color);
	g_env.ambl_distrib = scale_by(g_env.ambl_distrib, g_env.ambl_intensity);
	g_env.unique_amb = false;
}

void	parse_light(char **input)
{
	t_light *new_light;

	ft_printf("Parsing light...\n");
	new_light = malloc(sizeof(t_light));
	new_light->origin = parse_vec(input);
	new_light->intensity = parse_double(input);
	if (new_light->intensity < 0
		|| new_light->intensity > 1)
		die("Light intensity not in range [0,1]");
	new_light->color = parse_color(input);
	new_light->color_distribution = distribute_colors(new_light->color);
	new_light->color_distribution = scale_by(new_light->color_distribution,
												new_light->intensity);
	new_light->next = g_env.lights;
	g_env.lights = new_light;
}
