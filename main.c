/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:26 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 11:42:44 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_env	env;

double		sq(double value)
{
	return (value * value);
}

static void	env_checkup(void)
{
	if (env.res_x == 0 || env.res_x > env.res_xmax)
		env.res_x = env.res_xmax;
	if (env.res_y == 0 || env.res_y > env.res_ymax)
		env.res_y = env.res_ymax;
	if (env.has_res == false)
		die("You must provide a resolution");
	if (env.cameras == NULL)
		die("You must define at least one camera");
}

int			cleanup_and_quit(void)
{
	free_env(&env);
	exit(EXIT_SUCCESS);
	return (0);
}

int			main(int argc, char *argv[])
{
	init_env();
	check_args(argc, argv);
	env.scene_path = argv[1];
	check_rt_extension(env.scene_path);
	env.mlx_session = mlx_init();
	if (env.mlx_session == NULL)
		die("Failed to set up connection to the X server");
	mlx_get_screen_size(env.mlx_session, &env.res_xmax, &env.res_ymax);
	parse_file_into_env();
	env_checkup();
	create_images();
	render_image_list(env.images);
	if (env.bmp_mode)
		create_bmp();
	else
	{
		env.window = mlx_new_window(env.mlx_session, env.res_x, env.res_y, "");
		mlx_put_image_to_window(env.mlx_session, env.window,
									env.images->mlx_handle, 0, 0);
		mlx_key_hook(env.window, &handle_keypress, NULL);
		mlx_hook(env.window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
					&cleanup_and_quit, NULL);
		mlx_loop(env.mlx_session);
	}
	return (0);
}

t_vec3		canvas_to_viewport(int x, int y, double fov)
{
	t_vec3 ray;
	double aspect_ratio;
	double stretch;

	aspect_ratio = (double)env.res_x / (double)env.res_y;
	stretch = tan(fov * 0.5);
	ray.x = (2.0 * (x + 0.5) / (double)env.res_x - 1)
			* aspect_ratio
			* stretch;
	ray.y = (1 - 2.0 * (y + 0.5) / (double)env.res_y)
			* stretch;
	ray.z = 1;
	return (ray);
}
