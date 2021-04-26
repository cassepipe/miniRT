/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 18:44:13 by tpouget          ###   ########.fr       */
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

static bool		solve_2deg_eq(t_vec3 coeffs, double *sol1, double *sol2)
{
	double	delta;

	delta = (coeffs.y * coeffs.y) - (4 * coeffs.x * coeffs.z);
	if (delta < 0)
		return (false);
	*sol1 = (-coeffs.y + sqrt(delta)) / (2 * coeffs.x);
	*sol2 = (-coeffs.y - sqrt(delta)) / (2 * coeffs.x);
	return (true);
}

static bool		is_inside_cyl(t_cyl *cylinder, t_ray *ray, double t)
{
	t_vec3		hit_point;
	t_vec3		top;
	t_vec3		base_to_hit_point;
	t_vec3		top_to_hit_point;

	hit_point = add_vec(ray->origin, scale_by(ray->dir, t));
	top = add_vec(cylinder->base, scale_by(cylinder->dir, cylinder->height));
	base_to_hit_point = sub_vec(hit_point, cylinder->base);
	top_to_hit_point = sub_vec(hit_point, top);
	return ((dot(cylinder->dir, base_to_hit_point) > 0.0)
			&& (dot(cylinder->dir, top_to_hit_point) < 0.0));
}

static bool		get_cylinder_solutions(t_vec3 coeffs, t_ray *ray, t_cyl *cyl,
																	double *t)
{
	bool		ret;
	double		s1;
	double		s2;

	ret = false;
	s1 = INFINITY;
	s2 = INFINITY;
	if (solve_2deg_eq(coeffs, &s1, &s2))
	{
		if (s1 > ray->tmin && s1 < ray->tmax && is_inside_cyl(cyl, ray, s1))
		{
			*t = s1;
			ret = true;
		}
		if (s2 > ray->tmin && s2 < ray->tmax && is_inside_cyl(cyl, ray, s2))
		{
			if (s2 < s1)
			{
				*t = s2;
				ret = true;
			}
		}
	}
	return (ret);
}

bool			intersect_ray_with_cylinder(t_ray *ray, t_cyl *cyl,
																	double *t)
{
	t_vec3		coeffs;
	t_vec3		co;
	t_vec3		vec1;
	t_vec3		vec2;

	co = sub_vec(ray->origin, cyl->base);
	vec1 = sub_vec(ray->dir, scale_by(cyl->dir, dot(ray->dir, cyl->dir)));
	vec2 = sub_vec(co, scale_by(cyl->dir, dot(co, cyl->dir)));
	coeffs = get_equation_coeffs(vec1, vec2, cyl->diameter * 0.5);
	return (get_cylinder_solutions(coeffs, ray, cyl, t));
}
