#include "minirt.h"

void    create_images()
{
	struct s_image  *img_buf;
	int          i;

	img_buf = malloc(sizeof(t_image) * env.number_of_cams);
	if (!img_buf)
		die("malloc failed");
	img_buf[env.number_of_cams - 1].next = img_buf;
	i = 0;
	while(i < env.number_of_cams)
	{
		img_buf[i].mlx_handle = mlx_new_image(env.mlx_session, env.res_x, env.res_y);
		img_buf[i].data = mlx_get_data_addr(img_buf[i].mlx_handle,
				&img_buf[i].bits_per_pixel,
				&img_buf[i].line_len,
				&img_buf[i].endianness);
		img_buf[i].next = &img_buf[i+1];
		i++;
	}
	env.images = img_buf;
}
	/*env.images->mlx_handle = mlx_new_image(env.mlx_session, env.res_x, env.res_y);
	env.images->data = mlx_get_data_addr(env.images->mlx_handle,
										&env.images->bits_per_pixel,
										&env.images->line_len,
										&env.images->endianness);*/
