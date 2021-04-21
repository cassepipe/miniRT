#include "minirt.h"

void		check_args(int argc, char *argv[])
{
	if (argc != 2)
	{
		if (argc == 3)
		{
			if (!strcmp(argv[2], "--save"))
				env.bmp_mode = true;
			else if (argv[2][0] == '-')
				die("`--save` is the only valid option");
			else
				die("Too many arguments");
		}
		else if (argc == 1)
			die("You must provide an .rt file");
		else
			die("Too many arguments");
	}
}
