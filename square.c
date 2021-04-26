/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:27 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 16:53:15 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** https://stackoverflow.com/questions/40589161/check-if-point-belongs-to-square
*/

static bool	is_inside_square(t_vec3 hit_point, t_square *square)
{
	double	r;
	t_vec3	local;

	r = square->side_len * 0.5;
	local = sub_vec(hit_point, square->center);
	if (fabs(local.x) + fabs(local.y) + fabs(local.z) <= r)
		return (true);
	return (false);
}

bool		intersect_ray_with_square(t_ray *ray, t_square *square, double *t)
{
	bool	has_hit;
	t_vec3	hit_point;
	t_plane plane;

	plane.normal = square->normal;
	plane.some_point = square->center;
	has_hit = intersect_ray_with_plane(ray, &plane, t);
	if (!has_hit)
		return (false);
	hit_point = scale_by(ray->dir, *t);
	hit_point = add_vec(ray->origin, hit_point);
	if (!has_hit)
		return (false);
	has_hit = is_inside_square(hit_point, square);
	return (has_hit);
}
