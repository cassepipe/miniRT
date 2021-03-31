#include "minirt.h"


t_vec3		get_quad_coef(t_vec3 dir, t_vec3 oc, double radius);
static bool		solve_cylinder(t_cylinder *cylinder, t_vec3 *ray, t_vec3 quad_coef, double *t);
static t_vec3	pre_compute_coef(t_vec3 v1, t_vec3 v2);
bool		get_quad_roots(double *root1, double *root2, t_vec3 quad_coef);

t_vec3		get_quad_coef(t_vec3 dir, t_vec3 oc, double radius)
{
	t_vec3	result;

	result.x = dot(dir, dir);
	result.y = 2 * dot(dir, oc);
	result.z = dot(oc, oc) - (radius * radius);
	return (result);
}

static bool		solve_cylinder(t_cylinder *cylinder, t_vec3 *ray, t_vec3 quad_coef, double *t)
{
	double		root1;
	double		root2;
	bool		retvalue;

	root1 = INFINITY;
	root2 = INFINITY;
	retvalue = false;
	if (get_quad_roots(&root1, &root2, quad_coef))
	{
		if ((root1 > 1))
		{
			*t = root1;
			retvalue = true;
		}
		if ((root2 > 1))
		{
			if (root2 < root1)
			{
				*t = root2;
				retvalue = true;
			}
		}
	}
	return (retvalue);
}

static t_vec3	pre_compute_coef(t_vec3 v1, t_vec3 v2)
{
	return (substract_vec3(v1, scale_by(v2, dot(v1, v2))));
}

bool			intersect_ray_with_cylinder(t_vec3 *eye, t_vec3 *ray, t_cylinder *cylinder, double *t, double tmin, double tmax)
{
	t_vec3		quad_coef;
	t_vec3		oc;
	t_vec3		dir;
	t_vec3		ocdir;

	oc = substract_vec3(*eye, cylinder->base);
	dir = pre_compute_coef(*ray, cylinder->orientation);
	ocdir = pre_compute_coef(oc, cylinder->orientation);
	quad_coef = get_quad_coef(dir, ocdir, cylinder->diameter * 0.5);
	return (solve_cylinder(cylinder, ray, quad_coef, t));
}

bool		get_quad_roots(double *root1, double *root2, t_vec3 quad_coef)
{
	double	discr;

	discr = sq(quad_coef.y) - (4 * quad_coef.x * quad_coef.z);
	if (discr < 0.0)
		return (false);
	*root1 = (-quad_coef.y + sqrt(discr)) / (2 * quad_coef.x);
	*root2 = (-quad_coef.y - sqrt(discr)) / (2 * quad_coef.x);
	return (true);
}
