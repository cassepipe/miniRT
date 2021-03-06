#include "minirt.h"

void die(const char* error_text)
{
	//free_some_stuff();
	fprintf(stderr, error_text);
	exit(EXIT_FAILURE);
}
