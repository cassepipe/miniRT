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
	env.unique_res = true;
	env.has_res = false;
	env.ambl_intensity = DEFAULT_AMBIENT_LIGHT_INTENSITY;
	env.ambl_color = DEFAULT_AMBIENT_LIGHT_COLOR;
	env.ambl_distrib = DEFAULT_AMBIENT_LIGHT_COLOR_DISTRIB;
	env.unique_amb = true;
	env.lights = NULL;
	env.cameras = NULL;
	env.cameras = NULL;
	env.images = NULL;
	env.displayed_image = NULL;
	env.objects = NULL;
}
