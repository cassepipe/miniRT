/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 11:08:34 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersect_ray_with_sphere(t_vec3 *O, t_vec3 *ray, t_sphere *sphere, double *t,
										double tmin, double tmax)
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
	co = sub_vec(*O, sphere->center);
	a = dot(*ray, *ray);
	b = 2 * dot(co, *ray);
	c = dot(co, co) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);
	has_hit = false;
	solution = INFINITY;
	if (t1 > tmin && t1 < tmax)
	{
		solution = t1;
		has_hit = true;
	}
	if (t2 > tmin && t2 < tmax && t2 < solution)
	{
		solution = t2;
		has_hit = true;
	}
	*t = solution;
	return (has_hit);
}
