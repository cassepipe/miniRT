#include "minirt.h"

t_color	compute_sphere_lighting(t_vec3 *ray, t_vec3 *eye, t_sphere *sphere, double parameter)
{
		t_vec3 hit_point;
		t_vec3 normal;

		hit_point = scale_by(*ray, parameter);
		hit_point = add_vec(*eye, hit_point);

		normal = sub_vec(hit_point, sphere->center);  // Compute sphere normal at intersection
		normal = normalize(normal);

		return (apply_lighting(sphere->color, compute_lighting(hit_point, normal)));
}

t_color	compute_cylinder_lighting(t_vec3 *ray, t_vec3 *eye, t_cylinder *cylinder, double parameter)
{
		t_vec3 hit_point;
		t_vec3 normal;
		double m;
		t_vec3 CP;

		hit_point = add_vec(*eye, scale_by(*ray, parameter));

		CP = sub_vec(hit_point, cylinder->base);
		m = dot(cylinder->dir, CP);
		normal = sub_vec(CP, scale_by(cylinder->dir, m));
		normal = normalize(normal);

		return (apply_lighting(cylinder->color, compute_lighting(hit_point, normal)));

		/*if (dot(normal, *ray) > 0)*/
			/*return (apply_lighting(cylinder->color,*/
									/*compute_lighting(hit_point,*/
													/*scale_by(normal, -1))));*/
		/*else*/
			/*return (apply_lighting(cylinder->color, compute_lighting(hit_point, normal)));*/
}

t_color	compute_triangle_lighting(t_vec3 *ray, t_vec3 *eye, t_triangle *triangle, double parameter)
{
		t_vec3 hit_point;

		hit_point = scale_by(*ray, parameter);
		hit_point = add_vec(*eye, hit_point);

		if (dot(triangle->normal, *ray) > 0)
			return (apply_lighting(triangle->color,
									compute_lighting(hit_point,
													scale_by(triangle->normal, -1))));
		else
			return (apply_lighting(triangle->color, compute_lighting(hit_point, triangle->normal)));
}

t_color		compute_square_lighting(t_vec3 *ray, t_vec3 *eye, t_square *square, double parameter)
{
		t_vec3 hit_point;

		hit_point = scale_by(*ray, parameter);
		hit_point = add_vec(*eye, hit_point);

		if (dot(square->normal, *ray) > 0)
			return (apply_lighting(square->color,
									compute_lighting(hit_point,
													scale_by(square->normal, -1))));
		else
			return (apply_lighting(square->color, compute_lighting(hit_point, square->normal)));
}
t_color	compute_plane_lighting(t_vec3 *ray, t_vec3 *eye, t_plane *plane, double parameter)
{
		t_vec3 hit_point;

		hit_point = scale_by(*ray, parameter);
		hit_point = add_vec(*eye, hit_point);

		if (dot(plane->normal, *ray) > 0)
			return (apply_lighting(plane->color,
									compute_lighting(hit_point,
													scale_by(plane->normal, -1))));
		else
			return (apply_lighting(plane->color, compute_lighting(hit_point, plane->normal)));
}
