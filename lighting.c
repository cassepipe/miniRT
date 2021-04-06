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
		die("Could not compute light: Unrecognized object type");
	return (struct s_color){255,255,255};
}

double 	compute_lighting(t_vec3 hit_point, t_vec3 normal)
{
	double	i;
	t_light *light;
	t_vec3	light_vector;
	double	n_dot_l;

	i = env.ambl_ratio;
	//printf("ambl ratio is %f\n", i);
	light = env.lights;
	while (light != NULL && i < 1)
	{
		light_vector = substract_vec3(light->origin, hit_point);

			n_dot_l = dot(light_vector, normal);
			if (n_dot_l > 0)
			{
				if (!trace_light(&hit_point, &light_vector))
					i += light->ratio * n_dot_l/(vec_len(normal) * vec_len(light_vector));
			}
		light = light->next;
	}
	if (i > 1)
		return (1);
	//printf("returning ratio %.1f\n", i);
	return (i);
}


t_color	compute_sphere_lighting(t_vec3 *ray, t_vec3 *eye, t_sphere *sphere, double parameter)
{
		t_vec3 hit_point;
		t_vec3 normal;

		hit_point = scale_by(*ray, parameter);
		hit_point = add_vec(*eye, hit_point);

		normal = substract_vec3(hit_point, sphere->center);  // Compute sphere normal at intersection
		normal = normalize(normal);

		return (scale_color_by(sphere->color, compute_lighting(hit_point, normal)));
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

		return (scale_color_by(cylinder->color, compute_lighting(hit_point, normal)));
}

