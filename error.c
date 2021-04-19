#include "minirt.h"

void die(const char* error_text)
{
//	mlx_destroy_window(env.mlx_session, env.window);
	free_env(&env);
	ft_dprintf(STDERR_FILENO, error_text);
	exit(EXIT_FAILURE);
}
