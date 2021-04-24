/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:27 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 15:12:33 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

extern t_env g_env;

void	parse_sp(char **input)
{
	t_object	*new_object;
	t_sphere	*new_sphere;

	ft_printf("Parsing sphere...\n");
	new_sphere = malloc(sizeof(t_sphere));
	new_sphere->center = parse_vec(input);
	new_sphere->diameter = parse_double(input);
	new_sphere->color = parse_color(input);
	new_object = malloc(sizeof(t_object));
	new_object->id = SPHERE;
	new_object->data = new_sphere;
	new_object->next = g_env.objects;
	g_env.objects = new_object;
}

void	parse_pl(char **input)
{
	t_object	*new_object;
	t_plane		*new_plane;

	ft_printf("Parsing plane...\n");
	new_plane = malloc(sizeof(t_plane));
	new_plane->some_point = parse_vec(input);
	new_plane->normal = normalize(parse_vec(input));
	new_plane->color = parse_color(input);
	new_object = malloc(sizeof(t_object));
	new_object->id = PLANE;
	new_object->data = new_plane;
	new_object->next = g_env.objects;
	g_env.objects = new_object;
}

void	parse_sq(char **input)
{
	t_object	*new_object;
	t_square	*new_square;

	new_square = malloc(sizeof(t_square));
	new_square->center = parse_vec(input);
	new_square->normal = parse_vec(input);
	new_square->side_len = parse_double(input);
	new_square->color = parse_color(input);
	new_object = malloc(sizeof(t_object));
	new_object->id = SQUARE;
	new_object->data = new_square;
	new_object->next = g_env.objects;
	g_env.objects = new_object;
}

void	parse_cy(char **input)
{
	t_object	*new_object;
	t_cyl	*new_cylinder;

	ft_printf("Parsing cylinder...\n");
	new_cylinder = malloc(sizeof(t_cyl));
	new_cylinder->base = parse_vec(input);
	new_cylinder->dir = normalize(parse_vec(input));
	new_cylinder->diameter = parse_double(input);
	new_cylinder->height = parse_double(input);
	new_cylinder->color = parse_color(input);
	new_object = malloc(sizeof(t_object));
	new_object->id = CYLINDER;
	new_object->data = new_cylinder;
	new_object->next = g_env.objects;
	g_env.objects = new_object;
}

void	parse_tr(char **input)
{
	t_object	*new_object;
	t_triangle	*new_triangle;
	t_vec3		p1p2;
	t_vec3		p1p3;

	ft_printf("Parsing triangle...\n");
	new_triangle = malloc(sizeof(t_triangle));
	new_triangle->p1 = parse_vec(input);
	new_triangle->p2 = parse_vec(input);
	new_triangle->p3 = parse_vec(input);
	new_triangle->color = parse_color(input);
	p1p2 = sub_vec(new_triangle->p2, new_triangle->p1);
	p1p3 = sub_vec(new_triangle->p3, new_triangle->p1);
	new_triangle->normal = cross_product(p1p2, p1p3);
	new_triangle->normal = normalize(new_triangle->normal);
	new_object = malloc(sizeof(t_object));
	new_object->id = TRIANGLE;
	new_object->data = new_triangle;
	new_object->next = g_env.objects;
	g_env.objects = new_object;
}
