#include "minirt.h"

void    create_images()
{
	struct s_image  *img_buf;
	t_cam			*cam;
	int          i;

	img_buf = malloc(sizeof(t_image) * env.number_of_cams);
	if (!img_buf)
		die("Malloc failed");
	i = 0;
	cam = env.cameras;
	while(i < env.number_of_cams)
	{
		img_buf[i].mlx_handle = mlx_new_image(env.mlx_session, env.res_x, env.res_y);
		img_buf[i].data = mlx_get_data_addr(img_buf[i].mlx_handle,
				&img_buf[i].bits_per_pixel,
				&img_buf[i].line_len,
				&img_buf[i].endianness);
		img_buf[i].cam = cam;
		img_buf[i].next = &img_buf[i+1];
		cam = cam->next;
		i++;
	}
	img_buf[env.number_of_cams - 1].next = img_buf;
	env.images = img_buf;
	env.displayed_image = env.images;
}
