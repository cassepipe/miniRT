/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:50 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 16:06:00 by tpouget          ###   ########.fr       */
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

int		get_color_as_int(t_color color)
{
	int color_int;

	color_int = color.red << 16 | color.green << 8 | color.blue;
	return (color_int);
}

t_color	compute_ray_color(t_ray *ray, t_object *obj, double t)
{
	if (obj->id == SPHERE)
		return (compute_sphere_lighting(ray, (t_sphere*)(obj->data), t));
	if (obj->id == CYLINDER)
		return (compute_cylinder_lighting(ray, (t_cyl*)(obj->data), t));
	if (obj->id == PLANE)
		return (compute_plane_lighting(ray, (t_plane*)(obj->data), t));
	if (obj->id == TRIANGLE)
		return (compute_triangle_lighting(ray, (t_triangle*)(obj->data), t));
	if (obj->id == SQUARE)
		return (compute_square_lighting(ray, (t_square*)(obj->data), t));
	else
		die("Could not compute lighting: Unrecognized object type");
	return (BACKGROUND_COLOR);
}
