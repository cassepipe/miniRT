#include "minirt.h"

t_vec3	parse_vec(char **input)
{
	t_vec3 vector;

	vector.x = parse_double(input);
	vector.y = parse_double(input);
	vector.z = parse_double(input);
	return (vector);
}
