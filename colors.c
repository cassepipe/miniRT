/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:50 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/21 15:08:10 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	distribute_colors(t_color color)
{
	t_vec3 result;

	result.x = color.red / 255.0;
	result.y = color.green / 255.0;
	result.z = color.blue / 255.0;

	return (result);
}

int			get_color_as_int(t_color color)
{
	int color_int;

	color_int = color.red << 16 |  color.green << 8 | color.blue;

	return (color_int);
}

t_color	compute_ray_color(t_vec3 *ray, t_vec3 *eye, t_object *object, double parameter)
{
	if (object->id == SPHERE)
		return	(compute_sphere_lighting(ray, eye, (t_sphere*)(object->data), parameter));
	if (object->id == CYLINDER)
		return	(compute_cylinder_lighting(ray, eye, (t_cylinder*)(object->data), parameter));
	if (object->id == PLANE)
		return	(compute_plane_lighting(ray, eye, (t_plane*)(object->data), parameter));
	if (object->id == TRIANGLE)
		return	(compute_triangle_lighting(ray, eye, (t_triangle*)(object->data), parameter));
	if (object->id == SQUARE)
		return	(compute_square_lighting(ray, eye, (t_square*)(object->data), parameter));
	else
		die("Could not compute lighting: Unrecognized object type");
	return (struct s_color){255,255,255};
}
