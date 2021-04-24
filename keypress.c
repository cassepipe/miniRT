/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 14:33:52 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		handle_keypress(int keycode, void *params)
{
	(void)params;
	if (keycode == SPACE)
	{
		g_env.displayed_image = g_env.displayed_image->next;
		mlx_put_image_to_window(g_env.mlx_session,
								g_env.window,
								g_env.displayed_image->mlx_handle,
								0,
								0);
	}
	if (keycode == ESC)
	{
		free_env(&g_env);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
