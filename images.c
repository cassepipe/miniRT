/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 14:29:07 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_images(void)
{
	struct s_image	*img_buf;
	t_cam			*cam;
	int				i;

	img_buf = malloc(sizeof(t_image) * g_env.number_of_cams);
	if (!img_buf)
		die("Malloc failed");
	i = 0;
	cam = g_env.cameras;
	while (i < g_env.number_of_cams)
	{
		img_buf[i].mlx_handle = mlx_new_image(g_env.mlx_session,
												g_env.res_x, g_env.res_y);
		img_buf[i].data = mlx_get_data_addr(img_buf[i].mlx_handle,
				&img_buf[i].bits_per_pixel,
				&img_buf[i].line_len,
				&img_buf[i].endianness);
		img_buf[i].cam = cam;
		img_buf[i].next = &img_buf[i + 1];
		cam = cam->next;
		i++;
	}
	img_buf[g_env.number_of_cams - 1].next = img_buf;
	g_env.images = img_buf;
	g_env.displayed_image = g_env.images;
}

void	put_pixel_to_image(struct s_image *image, int x, int y, int color)
{
	char *dest;

	dest = image->data + y * image->line_len + x * (image->bits_per_pixel / 8);
	*(unsigned int*)dest = color;
}
