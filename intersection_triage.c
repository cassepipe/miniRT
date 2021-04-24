/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_triage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 11:02:40 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool		intersect_ray_with_object(t_vec3 *eye, t_vec3 *ray, t_object *object, double *solution, double tmin, double tmax)
{
	if (object->id == SPHERE)
		return (intersect_ray_with_sphere(eye, ray,
					(t_sphere*)(object->data), solution, tmin, tmax));
	if (object->id == CYLINDER)
		return (intersect_ray_with_cylinder(eye, ray,
					(t_cylinder*)(object->data), solution, tmin, tmax));
	if (object->id == PLANE)
		return (intersect_ray_with_plane(eye, ray,
					(t_plane*)(object->data), solution, tmin, tmax));
	if (object->id == TRIANGLE)
		return (intersect_ray_with_triangle(eye, ray,
					(t_triangle*)(object->data), solution, tmin, tmax));
	if (object->id == SQUARE)
		return (intersect_ray_with_square(eye, ray,
					(t_square*)(object->data), solution, tmin, tmax));
	else
		die("Intersection impossible : Unrecognized object type");
	return (0);
}
