#include "minirt.h"

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
		light_vector = sub_vec(light->origin, hit_point);
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

t_color	apply_lighting(t_color color, t_vec3 color_ratios)
{
	t_color result;

	result.red = color.red * color_ratios.x;
	result.green = color.green * color_ratios.y;
	result.blue = color.blue * color_ratios.z;

	return (result);
}

