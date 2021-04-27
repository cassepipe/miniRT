/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/27 14:49:22 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool		is_inside_triangle(t_vec3 hit_point, t_triangle *tr)
{
	t_vec3 v;
	t_vec3 a;
	t_vec3 b;

	v = sub_vec(tr->p2, tr->p3);
	a = cross_product(v, sub_vec(hit_point, tr->p3));
	b = cross_product(v, sub_vec(tr->p1, tr->p3));
	if (dot(a, b) < 0)
		return (false);
	v = sub_vec(tr->p1, tr->p3);
	a = cross_product(v, sub_vec(hit_point, tr->p3));
	b = cross_product(v, sub_vec(tr->p2, tr->p3));
	if (dot(a, b) < 0)
		return (false);
	v = sub_vec(tr->p1, tr->p2);
	a = cross_product(v, sub_vec(hit_point, tr->p2));
	b = cross_product(v, sub_vec(tr->p3, tr->p2));
	if (dot(a, b) < 0)
		return (false);
	return (true);
}

bool			intersect_ray_with_triangle(t_ray *ray, t_triangle *triangle,
																	double *t)
{
	bool	has_hit;
	t_vec3	hit_point;
	t_plane plane;

	plane.normal = triangle->normal;
	plane.some_point = triangle->p1;
	has_hit = intersect_ray_with_plane(ray, &plane, t);
	if (!has_hit)
		return (false);
	hit_point = scale_by(ray->dir, *t);
	hit_point = add_vec(ray->origin, hit_point);
	if (!has_hit)
		return (false);
	has_hit = is_inside_triangle(hit_point, triangle);
	return (has_hit);
}
