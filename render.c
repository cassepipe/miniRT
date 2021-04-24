/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:27 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 09:39:03 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static  void	render(struct s_image image, double fov)
{
	t_vec3 ray;
	t_color closest_object_color;
	int pixel_color;
	int	y;
	int x;

		y = 0;
		while (y <= env.res_y)
		{
			x = 0;
			while (x <= env.res_x)
			{
//				printf("Processing pixel(%d, %d)...\n", x, y);
				ray = canvas_to_viewport(x, y, fov);
				ray = apply_rotation_to_ray(ray, image.cam->cam_to_world);
				ray = normalize(ray);
				closest_object_color = trace_ray(&image.cam->origin, &ray);
				pixel_color = get_color_as_int(closest_object_color);
				put_pixel_to_image(&image, x, y, pixel_color);
				x++;
			}
			y++;
		}
}

void		render_image_list(struct s_image *images)
{
	int i;
	t_cam *cam;

	i = 0;
	cam = env.cameras;
	while(i < env.number_of_cams)
	{
		render(images[i], cam->fov);
		cam = cam->next;
		i++;
	}
}
