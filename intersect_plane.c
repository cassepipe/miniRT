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
