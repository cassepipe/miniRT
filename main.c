#include "minirt.h"

t_env	env;

static void		check_rt_extension(char *filename)
{
	size_t len;

	len = ft_strlen(filename);
	if (filename[len - 1] != 't'
		|| filename[len - 2] != 'r'
		|| filename[len - 3] != '.' )
		die("You must provide a .rt file");
}

static void		env_checkup()
{
	if (env.res_x == 0 || env.res_x > env.res_xmax)
		env.res_x = env.res_xmax;
	if (env.res_y == 0 || env.res_y > env.res_ymax)
		env.res_y = env.res_ymax;
	if (env.has_res == false)
		die("You must provide a resolution");
	if (env.cameras == NULL)
		die("You must define at least one camera");
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
	env_checkup();

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

double sq(double value)
{
	return (value * value);
}
