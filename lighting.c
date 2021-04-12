#include "minirt.h"

t_color	compute_ray_color(t_vec3 *ray, t_vec3 *eye, t_object *object, double parameter)
{
	if (object->id == SPHERE)
		return	(compute_sphere_lighting(ray, eye, (t_sphere*)(object->data), parameter));
	if (object->id == CYLINDER)
		return	(compute_cylinder_lighting(ray, eye, (t_cylinder*)(object->data), parameter));
	if (object->id == PLANE)
		return	(compute_plane_lighting(ray, eye, (t_plane*)(object->data), parameter));
	else
		die("Could not compute lighting: Unrecognized object type");
	return (struct s_color){255,255,255};
}

static void cap_vec(t_vec3 *vec)
{
	if (vec->x > 1)
		vec->x = 1;
	if (vec->y > 1)
		vec->y = 1;
	if (vec->z > 1)
		vec->z = 1;
}

t_vec3 	compute_lighting(t_vec3 hit_point, t_vec3 normal)
{
	t_vec3	total_distrib;
	t_vec3	temp_distrib;
	t_light *light;
	t_vec3	light_vector;
	double	n_dot_l;

	total_distrib = env.ambl_distrib;
	light = env.lights;
	while (light != NULL) //&& i < 1)
	{
		light_vector = substract_vec3(light->origin, hit_point);
		n_dot_l = dot(light_vector, normal);
		if (n_dot_l > 0)
		{
			if (!trace_light(&hit_point, &light_vector))
			{
				temp_distrib = scale_by(light->color_distribution, n_dot_l/vec_len(light_vector));
				total_distrib = add_vec(total_distrib, temp_distrib);
			}
		}
		light = light->next;
		cap_vec(&total_distrib);
	}
	return (total_distrib);
}


t_color	compute_sphere_lighting(t_vec3 *ray, t_vec3 *eye, t_sphere *sphere, double parameter)
{
		t_vec3 hit_point;
		t_vec3 normal;

		hit_point = scale_by(*ray, parameter);
		hit_point = add_vec(*eye, hit_point);

		normal = substract_vec3(hit_point, sphere->center);  // Compute sphere normal at intersection
		normal = normalize(normal);

		return (apply_lighting(sphere->color, compute_lighting(hit_point, normal)));
}

t_color	compute_cylinder_lighting(t_vec3 *ray, t_vec3 *eye, t_cylinder *cylinder, double parameter)
{
		t_vec3 hit_point;
		t_vec3 normal;
		double m;
		t_vec3 CO;
		t_vec3 OC;
		t_vec3 AC;
		t_vec3 CA;
		t_vec3 CP;

		CO = substract_vec3(*eye, cylinder->base);
		OC = substract_vec3(cylinder->base, *eye);

		hit_point = add_vec(*eye, scale_by(*ray, parameter));

		m = dot(*ray, cylinder->dir) ;
		m = m * parameter;
		m = m + dot(CO, *ray);

		CA = add_vec(OC, scale_by(cylinder->dir, m));
		AC = scale_by(CA, -1);

		CP =  add_vec(CO, hit_point);

		normal = add_vec(AC, CP);
		normal = normalize(normal);

		return (apply_lighting(cylinder->color, compute_lighting(hit_point, normal)));
}

