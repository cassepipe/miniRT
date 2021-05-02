/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:26 by tpouget           #+#    #+#             */
/*   Updated: 2021/05/02 13:52:57 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_env	g_env;

static void	env_checkup(void)
{
	if (g_env.res_x == 0 || g_env.res_x > g_env.res_xmax)
		g_env.res_x = g_env.res_xmax;
	if (g_env.res_y == 0 || g_env.res_y > g_env.res_ymax)
		g_env.res_y = g_env.res_ymax;
	if (g_env.has_res == false)
		die("You must provide a resolution");
	if (g_env.has_amb == false)
		die("You must provide an ambient light");
	if (g_env.cameras == NULL)
		die("You must define at least one camera");
}

static int	cleanup_and_quit(void)
{
	free_env(&g_env);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	reload_img(t_env *env)
{
	mlx_put_image_to_window(env->mlx_session,
							env->window,
							env->images->mlx_handle,
							0,
							0);
	return (0);
}

static void	display_scene(void)
{
	g_env.window = mlx_new_window(g_env.mlx_session, g_env.res_x, g_env.res_y,
			"miniRT");
	mlx_put_image_to_window(g_env.mlx_session, g_env.window,
			g_env.images->mlx_handle, 0, 0);
	mlx_key_hook(g_env.window, &handle_keypress, NULL);
	mlx_hook(g_env.window, DestroyNotify, StructureNotifyMask,
			&cleanup_and_quit, NULL);
	mlx_hook(g_env.window, MapNotify, StructureNotifyMask, &reload_img, &g_env);
	mlx_loop(g_env.mlx_session);
}

int			main(int argc, char *argv[])
{
	init_env();
	check_args(argc, argv);
	g_env.scene_path = argv[1];
	check_rt_extension(g_env.scene_path);
	g_env.mlx_session = mlx_init();
	if (g_env.mlx_session == NULL)
		die("Failed to set up connection to the X server");
	mlx_get_screen_size(g_env.mlx_session, &g_env.res_xmax, &g_env.res_ymax);
	parse_file_into_env();
	env_checkup();
	create_images();
	render_image_list(g_env.images);
	if (g_env.bmp_mode)
		create_bmp();
	else
		display_scene();
	return (0);
}
