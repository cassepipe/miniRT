/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:27 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/27 16:00:20 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	render(struct s_image image, double fov)
{
	t_ray	ray;
	t_color closest_object_color;
	int		pixel_color;
	int		y;
	int		x;

	y = 0;
	while (y <= g_env.res_y)
	{
		x = 0;
		while (x <= g_env.res_x)
		{
			ray.dir = canvas_to_viewport(x, y, fov);
			ray.dir = apply_rotation_to_ray(ray.dir, image.cam->cam_to_world);
			ray.dir = normalize(ray.dir);
			ray.origin = image.cam->origin;
			ray.tmin = 1;
			ray.tmax = INFINITY;
			closest_object_color = trace_ray(&ray);
			pixel_color = get_color_as_int(closest_object_color);
			put_pixel_to_image(&image, x, y, pixel_color);
			x++;
		}
		y++;
	}
}

void		render_image_list(struct s_image *images)
{
	int		i;
	t_cam	*cam;

	ft_printf("Rendering images...");
	i = 0;
	cam = g_env.cameras;
	while (i < g_env.number_of_cams)
	{
		render(images[i], cam->fov);
		cam = cam->next;
		i++;
	}
}
