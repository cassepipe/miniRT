/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 11:23:15 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3		get_quad_coef(t_vec3 dir, t_vec3 oc, double radius)
{
	t_vec3	result;

	result.x = dot(dir, dir);
	result.y = 2 * dot(dir, oc);
	result.z = dot(oc, oc) - (radius * radius);
	return (result);
}

bool		get_quad_roots(double *root1, double *root2, t_vec3 quad_coef)
{
	double	discr;

	discr = sq(quad_coef.y) - (4 * quad_coef.x * quad_coef.z);
	if (discr < 0.0)
		return (false);
	*root1 = (-quad_coef.y + sqrt(discr)) / (2 * quad_coef.x);
	*root2 = (-quad_coef.y - sqrt(discr)) / (2 * quad_coef.x);
	return (true);
}

static bool		is_inside_cyl(t_vec3 *eye, t_cylinder *cylinder, t_vec3 *ray, double t)
{
	t_vec3		hit_point;
	t_vec3		top;
	t_vec3		base_to_hit_point;
	t_vec3		top_to_hit_point;

	hit_point = add_vec(*eye, scale_by(*ray, t));
	top = add_vec(cylinder->base, scale_by(cylinder->dir, cylinder->height));
	base_to_hit_point = sub_vec(hit_point, cylinder->base);
	top_to_hit_point = sub_vec(hit_point, top);
	return ((dot(cylinder->dir, base_to_hit_point) > 0.0)
			&& (dot(cylinder->dir, top_to_hit_point) < 0.0));
}

static bool		solve_cylinder(t_vec3 *eye, t_cylinder *cylinder, t_vec3 *ray, t_vec3 quad_coef, double *t,
								double tmin, double tmax)
{
	double		root1;
	double		root2;
	bool		retvalue;

	root1 = INFINITY;
	root2 = INFINITY;
	retvalue = false;
	if (get_quad_roots(&root1, &root2, quad_coef))
	{
		if (root1 > tmin && root1 < tmax
				&& is_inside_cyl(eye, cylinder, ray, root1))
		{
			*t = root1;
			retvalue = true;
		}
		if (root2 > tmin && root2 < tmax
				&& is_inside_cyl(eye, cylinder, ray, root2))
		{
			if (root2 < root1)
			{
				*t = root2;
				retvalue = true;
			}
		}
	}
	return (retvalue);
}

static t_vec3	pre_compute_coef(t_vec3 v1, t_vec3 v2)
{
	return (sub_vec(v1, scale_by(v2, dot(v1, v2))));
}

bool			intersect_ray_with_cylinder(t_vec3 *eye, t_vec3 *ray, t_cylinder *cylinder, double *t, double tmin, double tmax)
{
	t_vec3		quad_coef;
	t_vec3		oc;
	t_vec3		dir;
	t_vec3		ocdir;

	oc = sub_vec(*eye, cylinder->base);
	dir = pre_compute_coef(*ray, cylinder->dir);
	ocdir = pre_compute_coef(oc, cylinder->dir);
	quad_coef = get_quad_coef(dir, ocdir, cylinder->diameter * 0.5);
	return (solve_cylinder(eye, cylinder, ray, quad_coef, t, tmin, tmax));
}

