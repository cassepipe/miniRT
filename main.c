#include "minirt.h"

t_env	env;

static void		check_rt_extension(char *filename)
{
	size_t len;

	len = ft_strlen(filename);
	if (filename[len -1] != 't'
		|| filename[len - 2] != 'r'
		|| filename[len - 3] != '.' )
		die("You must provide a .rt file");
}

int			main(int argc, char *argv[])
{

	init_env();
	check_args(argc, argv);

	env.scene_path = argv[1];
	check_rt_extension(env.scene_path);

	//Init X session
	env.mlx_session = mlx_init();
	if (env.mlx_session == NULL)
		die("Failed to set up connection to the X server");

	//Get screen size
	mlx_get_screen_size(env.mlx_session, &env.res_xmax, &env.res_ymax);

	//Parsing
	parse_file_into_env();
	if (env.res_x == 0 || env.res_x > env.res_xmax)
		env.res_x = env.res_xmax;
	if (env.res_y == 0 || env.res_y > env.res_ymax)
		env.res_y = env.res_ymax;
	if (env.cameras == NULL)
		die("You must define at least one camera");

	//Check parsing
	struct s_object *cur = env.objects;
	while (cur)
	{
		prints(cur);
		cur = cur->next;
	}

	//Create image
	create_images();

	//Rendering
	render_image_list(env.images);

	if (env.bmp_mode)
	{
		create_bmp();
	}
	else
	{
		//Create window
		env.window = mlx_new_window(env.mlx_session, env.res_x, env.res_y, "miniRT");

		mlx_put_image_to_window(env.mlx_session, env.window, env.images->mlx_handle, 0, 0);

		//Hooking
		mlx_key_hook(env.window, &handle_keypress, NULL);
		mlx_hook(env.window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK , &cleanup_and_quit, NULL);

		//Looping
		mlx_loop(env.mlx_session);
	}

	return (0);
}

int		cleanup_and_quit()
{
		free_env(&env);
		exit(EXIT_SUCCESS);
		return (0);
}

int		handle_keypress(int keycode, void *params)
{
	(void)params;
	if (keycode == SPACE)
	{
		env.displayed_image = env.displayed_image->next;
		mlx_put_image_to_window(env.mlx_session, env.window, env.displayed_image->mlx_handle, 0, 0);
	}
	if (keycode == ESC)
	{
		free_env(&env);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

t_vec3	apply_rotation_to_ray(t_vec3 ray, t_matrix3x3 rot_matrix)
{
	return (mult_matrix3x3_vec3(rot_matrix, ray));
}

t_matrix3x3	compute_cam_to_world_matrix(t_vec3 camera_direction)
{
	t_matrix3x3 result;

	t_vec3 arbitrary_vec;

	result.forward = normalize(camera_direction);
	if (result.forward.y == 1)
		arbitrary_vec = (t_vec3){0,0,-1};
	else if (result.forward.y == -1)
		arbitrary_vec = (t_vec3){0,0,1};
	else
		arbitrary_vec = (t_vec3){0,1,0};
	result.right = normalize(cross_product(arbitrary_vec, result.forward ));
	result.up = normalize(cross_product(result.forward, result.right));

	return (result);

}

void	put_pixel_to_image(struct s_image *image, int x, int y, int color)
{
	char *dest;

	dest = image->data + y * image->line_len + x * (image->bits_per_pixel/8);
	*(unsigned int*)dest = color;
}

t_vec3		canvas_to_viewport(int x, int y, double fov)
{
	t_vec3 ray;
	double aspect_ratio;
	double stretch;

	aspect_ratio = (double)env.res_x / (double)env.res_y;
	stretch = tan(fov * 0.5);
	ray.x = 	(2.0 * (x + 0.5) / (double)env.res_x - 1)
				* aspect_ratio
				* stretch;
	ray.y = (1 - 2.0 * (y + 0.5) / (double)env.res_y)
			* stretch;
	ray.z = 1;

//	printf("Corresponding to viewport coordinates (%f,%f)\n", ray.x, ray.y);

	return (ray);
}

bool		intersect_ray_with_object(t_vec3 *eye, t_vec3 *ray, t_object *object, double *solution, double tmin, double tmax)
{
	if (object->id == SPHERE)
		return	(intersect_ray_with_sphere(eye, ray, (t_sphere*)(object->data), solution, tmin, tmax));
	if (object->id == CYLINDER)
		return	(intersect_ray_with_cylinder(eye, ray, (t_cylinder*)(object->data), solution, tmin, tmax));
	if (object->id == PLANE)
		return	(intersect_ray_with_plane(eye, ray, (t_plane*)(object->data), solution, tmin, tmax));
	if (object->id == TRIANGLE)
		return	(intersect_ray_with_triangle(eye, ray, (t_triangle*)(object->data), solution, tmin, tmax));
	if (object->id == SQUARE)
		return	(intersect_ray_with_square(eye, ray, (t_square*)(object->data), solution, tmin, tmax));
	else
		die("Intersection impossible : Unrecognized object type");
	return (0);
}

double	autodot(t_vec3 v)
{
	return (dot(v, v));
}

double sq(double value)
{
	return (value * value);
}
