/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 11:05:22 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersect_ray_with_plane(t_vec3 *eye, t_vec3 *ray, t_plane *plane, double *t, double tmin, double tmax)
{
	double n_dot_d;
	double solution;
	t_vec3 eye_to_some_pt;

	n_dot_d = dot(plane->normal, *ray);
	if (n_dot_d != 0)
	{
		eye_to_some_pt = sub_vec(plane->some_point, *eye);
		solution = dot(plane->normal, eye_to_some_pt) / n_dot_d;
		if (solution > tmin && solution < tmax)
		{
			*t = solution;
			return (true);
		}
	}
	return (false);
}
