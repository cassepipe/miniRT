#include "minirt.h"

t_env	env;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		perror("You have not provided any arguments");
		return (0);
	}

	env.scene_path = argv[1];
	printf("scene path is %s\n", argv[1]);

	parse_file_into_env();
	return (0);
}
