#include "minirt.h"

void		init_env()
{
	env.mlx_session = NULL;
	env.window = NULL;
	env.scene_path = NULL;
	env.bmp_mode = false;
	env.number_of_cams = 0;
	env.res_x = 0;
	env.res_y = 0;
	env.res_xmax = 0;
	env.res_ymax = 0;
	env.ambl_intensity = 0;
	env.ambl_color = (t_color){.red = 0, .green = 0, .blue = 0};
	env.ambl_distrib = (t_vec3){.x = 0, .y = 0, .z = 0};
	env.lights = NULL;
	env.cameras = NULL;
	env.cameras = NULL;
	env.images = NULL;
	env.displayed_image = NULL;
	env.objects = NULL;
}
