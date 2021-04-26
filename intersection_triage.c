/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_triage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 10:42:59 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool		intersect_ray_with_object(t_ray *ray, t_object *obj, double *t, double tmin, double tmax)
{
	if (obj->id == SPHERE)
		return (intersect_ray_with_sphere(ray, (t_sphere*)(obj->data), t, tmin, tmax));
	if (obj->id == CYLINDER)
		return (intersect_ray_with_cylinder(ray, (t_cyl*)(obj->data), t, tmin, tmax));
	if (obj->id == PLANE)
		return (intersect_ray_with_plane(ray, (t_plane*)(obj->data), t, tmin, tmax));
	if (obj->id == TRIANGLE)
		return (intersect_ray_with_triangle(ray, (t_triangle*)(obj->data), t, tmin, tmax));
	if (obj->id == SQUARE)
		return (intersect_ray_with_square(ray, (t_square*)(obj->data), t, tmin, tmax));
	else
		die("Intersection impossible : Unrecognized object type");
	return (0);
}
