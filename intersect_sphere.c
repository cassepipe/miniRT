/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 16:49:32 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersect_ray_with_sphere(t_ray *ray, t_sphere *sphere, double *t)
{
	double	radius;
	t_vec3	co;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	double	solution;
	bool	has_hit;

	radius = sphere->diameter * 0.5;
	co = sub_vec(ray->origin, sphere->center);
	a = autodot(ray->dir);
	b = 2 * dot(co, ray->dir);
	c = dot(co, co) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);
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
