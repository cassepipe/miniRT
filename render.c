#include "minirt.h"

static  void	render(struct s_image image)
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
				printf("Processing pixel(%d, %d)...\n", x, y);
				ray = canvas_to_viewport(x, y);
				ray = apply_rotation_to_ray(ray, image.cam->cam_to_world);
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
	i = 0;
	while(i < env.number_of_cams)
	{
		render(images[i]);
		i++;
	}
}
