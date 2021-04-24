/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 11:11:09 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		handle_keypress(int keycode, void *params)
{
	(void)params;
	if (keycode == SPACE)
	{
		env.displayed_image = env.displayed_image->next;
		mlx_put_image_to_window(env.mlx_session,
								env.window,
								env.displayed_image->mlx_handle,
								0,
								0);
	}
	if (keycode == ESC)
	{
		free_env(&env);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
