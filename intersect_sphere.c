/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 18:01:44 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_equation_coeffs(t_vec3 dir, t_vec3 oc, double radius)
{
	t_vec3	result;

	result.x = dot(dir, dir);
	result.y = 2 * dot(dir, oc);
	result.z = dot(oc, oc) - (radius * radius);
	return (result);
}

bool			solve_2deg_eq(t_vec3 coeffs, double *sol1, double *sol2)
{
	double	discr;

	discr = (coeffs.y * coeffs.y) - (4 * coeffs.x * coeffs.z);
	if (discr < 0)
		return (false);
	*sol1 = (-coeffs.y + sqrt(discr)) / (2 * coeffs.x);
	*sol2 = (-coeffs.y - sqrt(discr)) / (2 * coeffs.x);
	return (true);
}

bool			intersect_ray_with_sphere(t_ray *ray, t_sphere *sphere,
																	double *t)
{
	t_vec3	coeffs;
	double	t1;
	double	t2;
	double	solution;
	bool	has_hit;

	coeffs = get_equation_coeffs(ray->dir, sub_vec(ray->origin, sphere->center),
														sphere->diameter * 0.5);
	if (!solve_2deg_eq(coeffs, &t1, &t2))
		return (false);
	has_hit = false;
	solution = INFINITY;
	if (t1 > ray->tmin && t1 < ray->tmax)
	{
		solution = t1;
		has_hit = true;
	}
	if (t2 > ray->tmin && t2 < ray->tmax && t2 < solution)
	{
		solution = t2;
		has_hit = true;
	}
	*t = solution;
	return (has_hit);
}
