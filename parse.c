#include "minirt.h"

/*
** Order matters ! Longer tokens must appear first.
*/

static struct s_fat_token token_table[] =
{
	{ "sp",		2,	&parse_sp	},
	{ "pl",		2,	&parse_pl	},
	{ "sq",		2,	&parse_sq	},
	{ "cy",		2,	&parse_cy	},
	{ "tr",		2,	&parse_tr	},
	{ "R",		1,	&parse_res 	},
	{ "A",		1,	&parse_ambl	},
	{ "c",		1,	&parse_cam	},
	{ "l",		1,	&parse_light}
};

extern t_env	env;

void parse_file_into_env()
{
	int			fd;
	size_t		i;
	char		*input;
	char		*to_free;

	fd = open(env.scene_path, O_RDONLY);
	if (fd < 0)
		die("This file does not seem to exist");
	while (get_next_line(fd, &input))
	{
		to_free = input;
		skip_blank(&input);
		i = 0;
		while (i < sizeof(token_table)/sizeof(token_table[0]))
		{
			if (*input == '\0' || *input == '\n' || *input == '"')
				break;
			if (!ft_strncmp(token_table[i].token, input , token_table[i].len))
			{
				skip_set(&input, token_table[i].token);
				token_table[i].token_func(&input);
				break;
			}
			i++;
		}
		free(to_free);
		if (i == sizeof(token_table)/sizeof(token_table[0]))
			die("Format error in .rt file : Invalid object token");
	}
	free(input);
	close(fd);
}

void parse_res(char **input)
{
	env.res_x = parse_double(input);
	env.res_y = parse_double(input);
	if (env.res_x > env.res_xmax)
		env.res_x = env.res_xmax;
	if (env.res_y > env.res_ymax)
		env.res_y = env.res_ymax;
}
void	parse_ambl(char **input)
{
	printf("Parsing ambient light...\n");
	skip_blank(input);
	env.ambl_intensity = parse_double(input);
	if (env.ambl_intensity < 0
		|| env.ambl_intensity > 1)
		die("Light intensity not in range");
	env.ambl_color = parse_color(input);
	env.ambl_distrib = distribute_colors(env.ambl_color);
	env.ambl_distrib = scale_by(env.ambl_distrib, env.ambl_intensity);
}

void parse_light(char **input)
{
	t_light *new_light;

	printf("Parsing light...\n");
	new_light = malloc(sizeof(t_light));
	new_light->origin = parse_vec(input);
	new_light->intensity = parse_double(input);
	if (new_light->intensity < 0
		|| new_light->intensity > 1)
		die("Light intensity not in range");
	new_light->color = parse_color(input);
	new_light->color_distribution = distribute_colors(new_light->color);
	new_light->color_distribution = scale_by(new_light->color_distribution, new_light->intensity);
	new_light->next = env.lights;
	env.lights = new_light;
}

static double to_radians(double angle)
{
	return(angle / 180 * M_PI);
}


void parse_cam(char **input)
{
	t_cam *new_cam;

	printf("Parsing cam ...\n");
	new_cam = malloc(sizeof(t_cam));
	new_cam->origin = parse_vec(input);
	new_cam->direction = parse_vec(input);
	new_cam->fov = to_radians(parse_double(input));
	if (new_cam->fov < 0
		|| new_cam->fov > 180)
		die("Field of view not in range [0,180]");
	new_cam->cam_to_world = compute_cam_to_world_matrix(new_cam->direction);
	new_cam->next = env.cameras;
	env.cameras = new_cam;
	env.number_of_cams++;
}
