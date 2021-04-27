/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:44:24 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/27 11:30:22 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	trace_ray(t_ray *ray)
{
	t_object	*closest_object;
	t_object	*current_object;
	bool		has_hit;
	double		t;
	double		closest_t;

	closest_object = NULL;
	current_object = g_env.objects;
	t = INFINITY;
	closest_t = INFINITY;
	while (current_object != NULL)
	{
		has_hit = intersect_ray_with_object(ray, current_object, &t);
		if (has_hit && t >= 1 && t < closest_t)
		{
			closest_t = t;
			closest_object = current_object;
		}
		current_object = current_object->next;
	}
	if (closest_object == NULL)
		return ((t_color){255, 255, 255});
	return (compute_ray_color(ray, closest_object, closest_t));
}

bool	trace_light(t_ray *ray)
{
	t_object	*current_object;
	bool		has_hit;
	double		parameter;

	current_object = g_env.objects;
	parameter = 1;
	while (current_object != NULL)
	{
		ray->tmin = EPSILON;
		ray->tmax = 1;
		has_hit = intersect_ray_with_object(ray, current_object, &parameter);
		if (has_hit)
		{
			return (true);
		}
		current_object = current_object->next;
	}
	return (false);
}
