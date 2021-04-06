#include "minirt.h"

bool		intersect_ray_with_sphere(t_vec3 * O,  t_vec3 *ray, t_sphere *sphere, double *t,
										double tmin, double tmax)
{
	double	radius;
	t_vec3	CO;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double  t1;
	double  t2;
	double	solution;
	bool	has_hit;

	/*printf("For ray [%f, %f, %f]\n", ray->x, ray->y, ray->z);*/
	radius = sphere->diameter * 0.5;
	CO = substract_vec3(*O, sphere->center);

	a = dot(*ray, *ray);
	b = 2 * dot(CO, *ray);
	c = dot(CO, CO) - radius*radius;

	discriminant = b*b - 4*a*c;

	/*printf("discriminant = %f\n", discriminant);*/
	if (discriminant < 0)
	{
		return 0;
	}

	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);

	/*printf("t1 = %f\n\n", t1);*/
	/*printf("t2 = %f\n\n", t2);*/

	has_hit = false;
	solution = INFINITY;
	if (t1 > tmin && t1 < tmax)
	{
		solution = t1;
		has_hit = true;
	}
	if (t2 > tmin && t2 < tmax && t2 < solution)
	{
		solution = t2;
		has_hit = true;
	}
	*t = solution;
	return (has_hit);
}
