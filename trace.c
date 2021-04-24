#include "minirt.h"

t_color		trace_ray(t_vec3 *eye, t_vec3 *ray)
{
	t_object	*closest_object;
	t_object	*current_object;
	bool		has_hit;
	double		t;
	double		closest_t;

	closest_object = NULL;
	current_object = g_env.objects;
	t = INFINITY;
	closest_t = INFINITY;
	while (current_object != NULL)
	{
		has_hit = intersect_ray_with_object(eye, ray, current_object, &t, 1
																, INFINITY);
		if (has_hit)
		{
			if (t >= 1 && t < closest_t)
			{
				closest_t = t;
				closest_object = current_object;
			}
		}
		current_object = current_object->next;
	}
	if (closest_object == NULL)
		return (BACKGROUND_COLOR);
	return (compute_ray_color(ray, eye, closest_object, closest_t));
}

bool	trace_light(t_vec3 *hit_point, t_vec3 *ray)
{
	t_object	*current_object;
	bool		has_hit;
	double		parameter;

	current_object = g_env.objects;
	parameter = 1;
	while (current_object != NULL)
	{
		has_hit = intersect_ray_with_object(hit_point, ray, current_object,
													&parameter, 0.00001, 1);
		if (has_hit)
		{
			return (true);
		}
		current_object = current_object->next;
	}
	return (false);
}
