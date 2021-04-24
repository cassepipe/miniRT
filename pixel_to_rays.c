/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_to_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:42:07 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 14:42:10 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3		canvas_to_viewport(int x, int y, double fov)
{
	t_vec3 ray;
	double aspect_ratio;
	double stretch;

	aspect_ratio = (double)g_env.res_x / (double)g_env.res_y;
	stretch = tan(fov * 0.5);
	ray.x = (2.0 * (x + 0.5) / (double)g_env.res_x - 1)
			* aspect_ratio
			* stretch;
	ray.y = (1 - 2.0 * (y + 0.5) / (double)g_env.res_y)
			* stretch;
	ray.z = 1;
	return (ray);
}
