/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:26 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/21 15:06:38 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix3x3	compute_cam_to_world_matrix(t_vec3 camera_direction)
{
	t_matrix3x3 result;

	t_vec3 arbitrary_vec;

	result.forward = normalize(camera_direction);
	if (result.forward.y == 1)
		arbitrary_vec = (t_vec3){0,0,-1};
	else if (result.forward.y == -1)
		arbitrary_vec = (t_vec3){0,0,1};
	else
		arbitrary_vec = (t_vec3){0,1,0};
	result.right = normalize(cross_product(arbitrary_vec, result.forward ));
	result.up = normalize(cross_product(result.forward, result.right));

	return (result);
}

t_matrix3x3		transpose_matrix3x3(t_matrix3x3 matrix)
{
	t_matrix3x3	result;

	result.right.x = matrix.right.x;
	result.right.y = matrix.up.x;
	result.right.z = matrix.forward.x;
	result.up.x = matrix.right.y;
	result.up.y = matrix.up.y;
	result.up.z = matrix.forward.y;
	result.forward.x = matrix.right.z;
	result.forward.y = matrix.up.z;
	result.forward.z = matrix.forward.z;
	return (result);
}

t_vec3			mult_matrix3x3_vec3(t_matrix3x3 matrix, t_vec3 v)
{
	t_vec3		result;
	t_matrix3x3	transposed;

	transposed = transpose_matrix3x3(matrix);
	result.x = dot(transposed.right, v);
	result.y = dot(transposed.up, v);
	result.z = dot(transposed.forward, v);
	return (result);
}

t_vec3	apply_rotation_to_ray(t_vec3 ray, t_matrix3x3 rot_matrix)
{
	return (mult_matrix3x3_vec3(rot_matrix, ray));
}
