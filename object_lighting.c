/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_lighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:56:11 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 16:11:19 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	compute_sphere_lighting(t_ray *ray, t_sphere *sphere,
		double parameter)
{
	t_vec3 hit_point;
	t_vec3 normal;

	hit_point = scale_by(ray->dir, parameter);
	hit_point = add_vec(ray->origin, hit_point);
	normal = sub_vec(hit_point, sphere->center);
	normal = normalize(normal);
	if (dot(normal, ray->dir) > 0)
		return (apply_lighting(sphere->color,
					compute_lighting(hit_point,
						scale_by(normal, -1))));
	else
		return (apply_lighting(sphere->color,
					compute_lighting(hit_point, normal)));
}

t_color	compute_cylinder_lighting(t_ray *ray, t_cyl *cylinder,
		double parameter)
{
	t_vec3 hit_point;
	t_vec3 normal;
	double m;
	t_vec3 ac;
	t_vec3 cp;

	hit_point = add_vec(ray->origin, scale_by(ray->dir, parameter));
	cp = sub_vec(hit_point, cylinder->base);
	m = dot(cylinder->dir, cp);
	ac = scale_by(cylinder->dir, m);
	normal = sub_vec(cp, ac);
	normal = normalize(normal);
	if (dot(normal, ray->dir) > 0)
		return (apply_lighting(cylinder->color,
					compute_lighting(hit_point,
						scale_by(normal, -1))));
	else
		return (apply_lighting(cylinder->color,
					compute_lighting(hit_point, normal)));
}

t_color	compute_triangle_lighting(t_ray *ray, t_triangle *triangle,
													double parameter)
{
	t_vec3 hit_point;

	hit_point = scale_by(ray->dir, parameter);
	hit_point = add_vec(ray->origin, hit_point);
	if (dot(triangle->normal, ray->dir) > 0)
		return (apply_lighting(triangle->color,
					compute_lighting(hit_point,
						scale_by(triangle->normal, -1))));
	else
		return (apply_lighting(triangle->color,
					compute_lighting(hit_point, triangle->normal)));
}

t_color	compute_square_lighting(t_ray *ray, t_square *square,
		double parameter)
{
	t_vec3 hit_point;

	hit_point = scale_by(ray->dir, parameter);
	hit_point = add_vec(ray->origin, hit_point);
	if (dot(square->normal, ray->dir) > 0)
		return (apply_lighting(square->color,
					compute_lighting(hit_point,
						scale_by(square->normal, -1))));
	else
		return (apply_lighting(square->color,
					compute_lighting(hit_point, square->normal)));
}

t_color	compute_plane_lighting(t_ray *ray, t_plane *plane,
		double parameter)
{
	t_vec3 hit_point;

	hit_point = scale_by(ray->dir, parameter);
	hit_point = add_vec(ray->origin, hit_point);
	if (dot(plane->normal, ray->dir) > 0)
		return (apply_lighting(plane->color,
					compute_lighting(hit_point,
						scale_by(plane->normal, -1))));
	else
		return (apply_lighting(plane->color,
					compute_lighting(hit_point, plane->normal)));
}
