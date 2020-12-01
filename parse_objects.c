#include "minirt.h"

extern t_env env;

void parse_sp(char **input)
{
	t_node		*new_node;
	t_sphere	*new_sphere;

	new_sphere = malloc(sizeof(t_sphere));
	new_sphere->center = parse_vec(input);
	new_sphere->diameter = parse_double_or_die(input);
	new_sphere->color = parse_vec(input);

	new_node = malloc(sizeof(t_node));
	new_node->id = SPHERE;
	new_node->object = new_sphere;
	new_node->next = env.objects;
	env.objects = new_node;
}

void parse_pl(char **input)
{
	t_node		*new_node;
	t_plane		*new_plane;

	new_plane = malloc(sizeof(t_plane));
	new_plane->some_point = parse_vec(input);
	new_plane->orientation = parse_vec(input);
	new_plane->color = parse_vec(input);

	new_node = malloc(sizeof(t_node));
	new_node->id = PLANE;
	new_node->object = new_plane;
	new_node->next = env.objects;
	env.objects = new_node;
}

void parse_sq(char **input)
{
	t_node			*new_node;
	t_square		*new_square;

	new_square = malloc(sizeof(t_square));
	new_square->center = parse_vec(input);
	new_square->orientation = parse_vec(input);
	new_square->side_len = parse_double_or_die(input);
	new_square->color = parse_vec(input);

	new_node = malloc(sizeof(t_node));
	new_node->id = SQUARE;
	new_node->object = new_square;
	new_node->next = env.objects;
	env.objects = new_node;
}

void parse_cy(char **input)
{
	t_node			*new_node;
	t_cylinder		*new_cylinder;

	new_cylinder = malloc(sizeof(t_square));
	new_cylinder->center = parse_vec(input);
	new_cylinder->orientation = parse_vec(input);
	new_cylinder->diameter = parse_double_or_die(input);
	new_cylinder->height = parse_double_or_die(input);
	new_cylinder->color = parse_vec(input);

	new_node = malloc(sizeof(t_node));
	new_node->id = CYLINDER;
	new_node->object = new_cylinder;
	new_node->next = env.objects;
	env.objects = new_node;
}

void parse_tr(char **input)
{
	t_node			*new_node;
	t_triangle		*new_triangle;

	new_triangle = malloc(sizeof(t_square));
	new_triangle->p1 = parse_vec(input);
	new_triangle->p2 = parse_vec(input);
	new_triangle->p3 = parse_vec(input);
	new_triangle->color = parse_vec(input);

	new_node = malloc(sizeof(t_node));
	new_node->id = TRIANGLE;
	new_node->next = env.objects;
	env.objects = new_node;
}
