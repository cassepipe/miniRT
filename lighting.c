/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:42:22 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 18:50:30 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	cap_vec(t_vec3 *vec)
{
	if (vec->x > 1)
		vec->x = 1;
	if (vec->y > 1)
		vec->y = 1;
	if (vec->z > 1)
		vec->z = 1;
}

t_vec3		compute_lighting(t_vec3 hit_point, t_vec3 normal)
{
	t_vec3	total_distrib;
	t_light *light_point;
	t_ray	light_ray;
	double	n_dot_l;

	total_distrib = g_env.ambl_distrib;
	light_point = g_env.lights;
	while (light_point != NULL)
	{
		light_ray.dir = sub_vec(light_point->origin, hit_point);
		light_ray.origin = hit_point;
		n_dot_l = dot(light_ray.dir, normal);
		if (n_dot_l > 0)
		{
			if (!trace_light(&light_ray))
				total_distrib = add_vec(total_distrib,
										scale_by(light_point->color_distrib,
											n_dot_l / vec_len(light_ray.dir)));
		}
		light_point = light_point->next;
		cap_vec(&total_distrib);
	}
	return (total_distrib);
}

t_color		apply_lighting(t_color color, t_vec3 color_ratios)
{
	t_color result;

	result.red = color.red * color_ratios.x;
	result.green = color.green * color_ratios.y;
	result.blue = color.blue * color_ratios.z;
	return (result);
}
