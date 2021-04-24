/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_triage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 16:01:09 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool		intersect_ray_with_object(t_ray *ray, t_object *object, double *t, double tmin, double tmax)
{
	if (object->id == SPHERE)
		return (intersect_ray_with_sphere(ray, (t_sphere*)(object->data), t, tmin, tmax));
	if (object->id == CYLINDER)
		return (intersect_ray_with_cylinder(ray, (t_cyl*)(object->data), t, tmin, tmax));
	if (object->id == PLANE)
		return (intersect_ray_with_plane(ray, (t_plane*)(object->data), t, tmin, tmax));
	if (object->id == TRIANGLE)
		return (intersect_ray_with_triangle(ray, (t_triangle*)(object->data), t, tmin, tmax));
	if (object->id == SQUARE)
		return (intersect_ray_with_square(ray, (t_square*)(object->data), t, tmin, tmax));
	else
		die("Intersection impossible : Unrecognized object type");
	return (0);
}
