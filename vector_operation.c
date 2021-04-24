/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:27 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 12:26:24 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	scale_by(t_vec3 vector, double scalar)
{
	t_vec3 result;

	result.x = vector.x * scalar;
	result.y = vector.y * scalar;
	result.z = vector.z * scalar;
	return (result);
}

t_vec3	add_vec(t_vec3 v1, t_vec3 v2)
{
	t_vec3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

double	vec_len(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	normalize(t_vec3 v)
{
	double len;
	t_vec3 result;

	len = vec_len(v);
	result.x = v.x / len;
	result.y = v.y / len;
	result.z = v.z / len;
	return (result);
}

t_vec3		sub_vec(t_vec3 point1, t_vec3 point2)
{
	t_vec3 vector;

	vector.x = point1.x - point2.x;
	vector.y = point1.y - point2.y;
	vector.z = point1.z - point2.z;
	return (vector);
}
