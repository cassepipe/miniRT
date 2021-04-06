#include "minirt.h"

bool	intersect_ray_with_plane(t_vec3 *eye, t_vec3 *ray, t_plane *plane, double *t, double tmin, double tmax)
{
	double NdotD;
	t_vec3 eye_to_some_pt;

	NdotD = dot(plane->normal, *ray);
	if (fabs(NdotD) > EPSILON)
	{
		eye_to_some_pt = substract_vec3(plane->some_point, *eye);
		*t = dot(plane->normal, eye_to_some_pt) / NdotD;
		if (*t > 1)
			return true;
	}

	return false;
}

t_color	compute_plane_lighting(t_vec3 *ray, t_vec3 *eye, t_plane *plane, double parameter)
{
		t_vec3 hit_point;

		hit_point = scale_by(*ray, parameter);
		hit_point = add_vec(*eye, hit_point);

		if (dot(plane->normal, *ray) < 0)
			return (scale_color_by(plane->color,
									compute_lighting(hit_point,
													scale_by(plane->normal, -1))));
		else
			return (scale_color_by(plane->color, compute_lighting(hit_point, plane->normal)));
}
