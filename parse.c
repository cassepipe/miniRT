#include "minirt.h"

static struct s_fat_token token_table[] =
{
	{ "R",	1,	&parse_res 	},
	{ "A",	1,	&parse_ambl	},
	{ "c",	1,	&parse_cam	},
	{ "l",	1,	&parse_light},
	{ "sp",	1,	&parse_sp	},
	{ "pl",	2,	&parse_pl	},
	{ "sq",	2,	&parse_sq	},
	{ "cy",	2,	&parse_cy	},
	{ "tr",	2,	&parse_tr	}
};

extern t_env	env;

void parse_file_into_env()
{
	char	*input;
	int		fd;
	int		i;

	fd = open(env.scene_path, O_RDONLY);
	while (get_next_line(fd, &input))
	{
		skip_blank(&input);
		i = 0;
		while (i++ < sizeof(token_table))
		{
			if (!strncmp(token_table[i].token, input , token_table[i].len))
			{
				skip_set(&input, token_table[i].token);
				token_table[i].token_func(&input);
			}
			else
				die();
		}
	}
}

void	parse_ambl(char **input)
{
	skip_blank(input);
	env.ambl_ratio = parse_double(input);
	env.ambl_color = parse_vec(input);
}

void parse_res(char **input)
{
	env.res_x = parse_double(input);
	env.res_y = parse_double(input);
}

void parse_cam(char **input)
{
	t_cam *new_cam;

	new_cam = malloc(sizeof(t_cam));
	new_cam->origin = parse_vec(input);
	new_cam->direction = parse_vec(input);
	new_cam->fov = parse_double(input);
	new_cam->next = env.cameras;
	env.cameras = new_cam;
}

void parse_light(char **input)
{
	t_light *new_light;

	new_light = malloc(sizeof(t_light));
	new_light->origin = parse_vec(input);
	new_light->ratio = parse_double(input);
	new_light->color = parse_vec(input);
	new_light->next = env.lights;
	env.lights = new_light;
}
