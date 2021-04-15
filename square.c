#include "minirt.h"

/*
** https://stackoverflow.com/questions/40589161/check-if-point-belongs-to-square
*/

static bool	is_inside_square(t_vec3 hit_point , t_square *square)
{
	double	r;
	t_vec3	local;

	r = square->side_len * 0.5;
	local = substract_vec3(hit_point, square->center);
	if (fabs(local.x) + fabs(local.y) + fabs(local.z) <= r)
		return true;
	return false;
}

bool intersect_ray_with_square(t_vec3 *eye, t_vec3 *ray, t_square *square, double *t, double tmin, double tmax)
{
	bool	has_hit;
	t_vec3	hit_point;
	t_plane plane;

	plane.normal = square->normal;
	plane.some_point = square->center;

	has_hit = intersect_ray_with_plane(eye, ray, &plane, t, tmin, tmax);
	if (!has_hit)
		return (false);
	hit_point = scale_by(*ray, *t);
	hit_point = add_vec(*eye, hit_point);
	if (!has_hit)
		return (false);
	has_hit = is_inside_square(hit_point, square);
	return (has_hit);
}
