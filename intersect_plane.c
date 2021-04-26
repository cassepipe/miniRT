/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 16:49:31 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersect_ray_with_plane(t_ray *ray, t_plane *plane, double *t)
{
	double n_dot_d;
	double solution;
	t_vec3 eye_to_some_pt;

	n_dot_d = dot(plane->normal, ray->dir);
	if (n_dot_d != 0)
	{
		eye_to_some_pt = sub_vec(plane->some_point, ray->origin);
		solution = dot(plane->normal, eye_to_some_pt) / n_dot_d;
		if (solution > ray->tmin && solution < ray->tmax)
		{
			*t = solution;
			return (true);
		}
	}
	return (false);
}
