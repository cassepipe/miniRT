#include "minirt.h"

double dot(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y +  u.z * v.z);
}

double	autodot(t_vec3 v)
{
	return (dot(v, v));
}

t_vec3	cross_product(t_vec3 a, struct s_vec3 b)
{
	t_vec3 result;

	result.x  = a.y*b.z - a.z*b.y;
	result.y  = a.z*b.x - a.x*b.z;
	result.z  = a.x*b.y - a.y*b.x;

	return (result);

}
