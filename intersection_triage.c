/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_triage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 16:47:29 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool		intersect_ray_with_object(t_ray *ray, t_object *obj, double *t)
{
	if (obj->id == SPHERE)
		return (intersect_ray_with_sphere(ray, (t_sphere*)(obj->data), t));
	if (obj->id == CYLINDER)
		return (intersect_ray_with_cylinder(ray, (t_cyl*)(obj->data), t));
	if (obj->id == PLANE)
		return (intersect_ray_with_plane(ray, (t_plane*)(obj->data), t));
	if (obj->id == TRIANGLE)
		return (intersect_ray_with_triangle(ray, (t_triangle*)(obj->data), t));
	if (obj->id == SQUARE)
		return (intersect_ray_with_square(ray, (t_square*)(obj->data), t));
	else
		die("Intersection impossible : Unrecognized object type");
	return (0);
}
