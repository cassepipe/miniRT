/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/27 21:42:43 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		init_env(void)
{
	g_env.mlx_session = NULL;
	g_env.window = NULL;
	g_env.scene_path = NULL;
	g_env.bmp_mode = false;
	g_env.number_of_cams = 0;
	g_env.res_x = 0;
	g_env.res_y = 0;
	g_env.res_xmax = 0;
	g_env.res_ymax = 0;
	g_env.unique_res = true;
	g_env.has_res = false;
	g_env.ambl_intensity = DEFAULT_AMBIENT_LIGHT_INTENSITY;
	g_env.ambl_color = (t_color){255, 255, 255};
	g_env.ambl_distrib = (t_vec3){1, 1, 1};
	g_env.unique_amb = true;
	g_env.has_amb = false;
	g_env.lights = NULL;
	g_env.cameras = NULL;
	g_env.cameras = NULL;
	g_env.images = NULL;
	g_env.displayed_image = NULL;
	g_env.objects = NULL;
}
