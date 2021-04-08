#include "minirt.h"

t_matrix3x3		transpose_matrix3x3(t_matrix3x3 mat)
{
	t_matrix3x3	result;

	result.right.x = mat.right.x;
	result.right.y = mat.up.x;
	result.right.z = mat.forward.x;
	result.up.x = mat.right.y;
	result.up.y = mat.up.y;
	result.up.z = mat.forward.y;
	result.forward.x = mat.right.z;
	result.forward.y = mat.up.z;
	result.forward.z = mat.forward.z;
	return (result);
}

t_matrix3x3		invert_matrix3x3(t_matrix3x3 matrix)
{
	t_matrix3x3	result;
	t_vec3		v_x;
	t_vec3		v_y;
	t_vec3		v_z;

	v_x = new_vec3(matrix.right.x, matrix.up.x, matrix.forward.x);
	v_x = scale_by(v_x, 1 / sq(vec_len(v_x)));
	v_y = new_vec3(matrix.right.y, matrix.up.y, matrix.forward.y);
	v_y = scale_by(v_x, (1 / sq(vec_len(v_y))));
	v_z = new_vec3(matrix.right.z, matrix.up.z, matrix.forward.z);
	v_z = scale_by(v_z, (1 / sq(vec_len(v_z))));
	result.right = new_vec3(v_x.x, v_x.y, v_x.z);
	result.up = new_vec3(v_y.x, v_y.y, v_y.z);
	result.forward = new_vec3(v_z.x, v_z.y, v_z.z);
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
