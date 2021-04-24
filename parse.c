/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:26 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 14:33:06 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Order matters ! Longer tokens must appear first.
*/

static struct s_fat_token token_table[] =
{
	{ "sp", 2, &parse_sp	},
	{ "pl", 2, &parse_pl	},
	{ "sq", 2, &parse_sq	},
	{ "cy", 2, &parse_cy	},
	{ "tr", 2, &parse_tr	},
	{ "R", 1, &parse_res	},
	{ "A", 1, &parse_ambl	},
	{ "c", 1, &parse_cam	},
	{ "l", 1, &parse_light}
};

static void		parse_tokens(char **input)
{
	char		*to_free;
	size_t		i;

	to_free = *input;
	skip_blank(input);
	i = 0;
	while (i < sizeof(token_table) / sizeof(token_table[0]))
	{
		if (**input == '\0' || **input == '\n' || **input == '"')
			break ;
		if (!ft_strncmp(token_table[i].token, *input, token_table[i].len))
		{
			skip_set(input, token_table[i].token);
			token_table[i].token_func(input);
			break ;
		}
		i++;
	}
	free(to_free);
	if (i == sizeof(token_table) / sizeof(token_table[0]))
		die("Format error in .rt file : Invalid object token");
}

void			parse_file_into_env(void)
{
	int			fd;
	char		*input;

	fd = open(g_env.scene_path, O_RDONLY);
	if (fd < 0)
		die("This file does not seem to exist");
	while (get_next_line(fd, &input))
	{
		parse_tokens(&input);
	}
	free(input);
	close(fd);
}

void			parse_res(char **input)
{
	g_env.has_res = true;
	if (!g_env.unique_res)
		die("Two resolutions defined. Only one is allowed");
	g_env.res_x = parse_int(input);
	g_env.res_y = parse_int(input);
	if (g_env.res_x < 0 || g_env.res_y < 0)
		die("Cannot take negative resolution values");
	g_env.unique_res = false;
}

static double	to_radians(double angle)
{
	return (angle / 180 * M_PI);
}

void			parse_cam(char **input)
{
	t_cam *new_cam;

	ft_printf("Parsing cam ...\n");
	new_cam = malloc(sizeof(t_cam));
	new_cam->origin = parse_vec(input);
	new_cam->direction = parse_vec(input);
	new_cam->fov = to_radians(parse_double(input));
	if (new_cam->fov < 0
		|| new_cam->fov > 180)
		die("Field of view not in range [0,180]");
	new_cam->cam_to_world = compute_cam_to_world_matrix(new_cam->direction);
	new_cam->next = g_env.cameras;
	g_env.cameras = new_cam;
	g_env.number_of_cams++;
}
