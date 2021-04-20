#include "minirt.h"

t_vec3	distribute_colors(t_color color)
{
	t_vec3 result;

	result.x = color.red / 255.0;
	result.y = color.green / 255.0;
	result.z = color.blue / 255.0;

	return (result);
}

int			get_color_as_int(t_color color)
{
	int color_int;

	color_int = color.red << 16 |  color.green << 8 | color.blue;

	return (color_int);
}
