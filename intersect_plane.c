/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/21 15:06:36 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersect_ray_with_plane(t_vec3 *eye, t_vec3 *ray, t_plane *plane, double *t, double tmin, double tmax)
{
	double NdotD;
	double solution;
	t_vec3 eye_to_some_pt;

	solution = INFINITY;
	NdotD = dot(plane->normal, *ray);
	if (NdotD != 0)
	{
		eye_to_some_pt = sub_vec(plane->some_point, *eye);
		solution = dot(plane->normal, eye_to_some_pt) / NdotD;
		if (solution > tmin && solution < tmax)
		{
			*t = solution;
			return true;
		}
	}

	return false;
}
