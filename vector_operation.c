#include "minirt.h"

t_vec3	scale_by(t_vec3 vector, double scalar)
{
	t_vec3 result;

	result.x = vector.x * scalar;
	result.y = vector.y * scalar;
	result.z = vector.z * scalar;

	return (result);
}

t_color	apply_lighting(t_color color, t_vec3 color_ratios)
{
	t_color result;

	result.red = color.red * color_ratios.x;
	result.green = color.green * color_ratios.y;
	result.blue = color.blue * color_ratios.z;

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

double	vec_len(t_vec3	v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

t_vec3 normalize(t_vec3 v)
{
	double len;
	t_vec3 result;

	len = vec_len(v);

	result.x = v.x / len;
	result.y = v.y / len;
	result.z = v.z / len;

	return (result);
}

t_vec3 new_vec3(double x, double y, double z)
{
	t_vec3 vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;

	return (vector);
}

t_vec3		substract_vec3(t_vec3 point1, t_vec3 point2)
{
	t_vec3 vector;

	vector.x = point1.x - point2.x;
	vector.y = point1.y - point2.y;
	vector.z = point1.z - point2.z;

	return (vector);

}

double dot(t_vec3 u, t_vec3 v)
{

	return (u.x * v.x + u.y * v.y +  u.z * v.z);
}

t_vec3	cross_product(t_vec3 a, struct s_vec3 b)
{
	t_vec3 result;

	result.x  = a.y*b.z - a.z*b.y;
	result.y  = a.z*b.x - a.x*b.z;
	result.z  = a.x*b.y - a.y*b.x;

	return (result);

}
