#include "minirt.h"

t_env	env;

void		init_env()
{
	env.objects = NULL;
	env.cameras = NULL;
	env.lights = NULL;
	env.images = NULL;
	env.number_of_cams = 0;
}

void		render(struct s_image image)
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
				//printf("Processing pixel(%d, %d)...\n", x, y);
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

int			main(int argc, char *argv[])
{

	if (argc != 2)
	{
		perror("You have not provided any arguments");
		return (0);
	}

	env.scene_path = argv[1];

	init_env();
	parse_file_into_env();

	//Check parsing
	struct s_object *cur = env.objects;
	while (cur)
	{
		prints(cur);
		cur = cur->next;
	}

	//Create window
	env.mlx_session = mlx_init();
	if (env.mlx_session == NULL)
		die("Failed to set up connection to X server");
	env.window = mlx_new_window(env.mlx_session, env.res_x, env.res_y, "miniRT");

	//Create image
	create_images();

	//Rendering
	render_image_list(env.images);

	mlx_put_image_to_window(env.mlx_session, env.window, env.images->mlx_handle, 0, 0);

	//Hooking
	mlx_key_hook(env.window, &handle_keypress, NULL);
	mlx_hook(env.window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK , &cleanup_and_quit, NULL);

	//Looping
	mlx_loop(env.mlx_session);

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

	/*result.forward = normalize(camera_direction);*/
	/*if (result.forward.y == 1)*/
		/*return (t_matrix3x3){{1,0,0},{0,0,-1},{0,1,0}};*/
	/*else if (result.forward.y == -1)*/
		/*return (t_matrix3x3){{1,0,0},{0,0,1},{0,-1,0}};*/
	/*else*/
		/*result.right = normalize(cross_product((t_vec3){0,1,0}, result.forward ));*/
	/*result.up = normalize(cross_product(result.forward, result.right));*/


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

int			get_color_as_int(t_color color)
{
	int color_int;

	color_int = color.red << 16 |  color.green << 8 | color.blue;

	return (color_int);
}

t_vec3		canvas_to_viewport(int x, int y)
{
	t_vec3 ray;

	ray.x = -env.res_x * 0.5 + x;
	ray.y = env.res_y * 0.5 - y;
	ray.z = 1;

	ray.x = ray.x / env.res_x;
	ray.y = ray.y / env.res_y;
	/*printf("Corresponding to viewport coordinates (%f,%f)\n", ray.x, ray.y);*/

	return (ray);
}

t_color		trace_ray(t_vec3 *eye, t_vec3 *ray)
{
	t_object	*closest_object;
	t_object	*current_object;
	bool		has_hit;
	double		t;
	double		closest_t;

	closest_object = NULL;
	current_object = env.objects;
	has_hit = false;
	t = INFINITY;
	closest_t = INFINITY;

	while (current_object != NULL)
	{
		//printf("Current object is %p\n", current_object);
		has_hit = intersect_ray_with_object(eye, ray, current_object, &t, 1, INFINITY);
		if (has_hit)
		{
			if (t >= 1 && t < closest_t)
			{
				closest_t = t;
				closest_object = current_object;
			}
		}
		current_object = current_object->next;
	}
	if (closest_object == NULL)
		return (struct s_color){255,255,255};

	return compute_ray_color(ray, eye, closest_object, closest_t);
}

bool	trace_light(t_vec3 *hit_point, t_vec3 *ray)
{
	t_object	*current_object;
	bool		has_hit;
	double		parameter;

	current_object = env.objects;
	has_hit = false;
	parameter = 1;
	while (current_object != NULL)
	{
		//printf("Current object is %p\n", current_object);
		has_hit = intersect_ray_with_object(hit_point, ray, current_object, &parameter, 0.00001, 1);
		if (has_hit)
		{
			return true;
		}
		current_object = current_object->next;
	}
	return false;
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

t_color get_object_color(t_object *object)
{
	if (object->id == SPHERE)
		return ((t_sphere*)object->data)->color;
	if (object->id == CYLINDER)
		return ((t_sphere*)object->data)->color;
	if (object->id == SQUARE)
		return ((t_sphere*)object->data)->color;
	if (object->id == PLANE)
		return ((t_sphere*)object->data)->color;
	if (object->id == TRIANGLE)
		return ((t_sphere*)object->data)->color;
	die("Wrong object id while in get_obj_color");
	return ((t_color){255,255,255});
}

void prints(struct s_object *object)
{
	if (!object)
		printf("The object points to NULL\n");
	else if (!(object->data))
		printf("No data to print in this object\n");
	else if (object->id == SQUARE)
	{
		t_square* square;
		square = object->data;

		printf("Square:\t\t");
		printf("Center is at (%.1f, %.1f, %.1f)\t", square->center.x, square->center.y, square->center.x);
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", square->dir.x, square->dir.y, square->dir.z);
		printf("Side lenght is %.1f\t", square->side_len);
		printf("RGB is (%d, %d, %d)\t", square->color.red, square->color.green, square->color.blue);
		printf("\n");
	}
	else if (object->id == CYLINDER)
	{
		t_cylinder* cyl;
		cyl = object->data;

		printf("Cylinder:\t");
		printf("Center is at (%.1f, %.1f, %.1f)\t", cyl->base.x, cyl->base.y, cyl->base.z);
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", cyl->dir.x, cyl->dir.y, cyl->dir.z);
		printf("Diameter is %.1f\t", cyl->diameter);
		printf("Height is %.1f\t", cyl->height);
		printf("RGB is (%d, %d, %d)\t", cyl->color.red, cyl->color.green, cyl->color.blue);
		printf("\n");
	}
	else if (object->id == PLANE)
	{
		t_plane* plane;
		plane = object->data;

		printf("Plane:\t\t");
		printf("Point is at (%.1f, %.1f, %.1f)\t", plane->some_point.x, plane->some_point.y, plane->some_point.x);
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", plane->normal.x, plane->normal.y, plane->normal.z);
		printf("RGB is (%d, %d, %d)\t", plane->color.red, plane->color.green, plane->color.blue);
		printf("\n");
	}
	else if (object->id == SPHERE)
	{
		t_sphere* sphere;
		sphere = object->data;

		printf("Sphere:\t\t");
		printf("Center is at (%.1f, %.1f, %.1f)\t", sphere->center.x, sphere->center.y, sphere->center.z);
		printf("Diameter is %.1f\t", sphere->diameter);
		printf("RGB is (%d, %d, %d)\t", sphere->color.red, sphere->color.green, sphere->color.blue);
		printf("\n");
	}
	else if (object->id == TRIANGLE)
	{
		t_triangle* triangle;
		triangle = object->data;

		printf("Triangle:\t\t\n");
		printf("Point 1 is at (%.1f, %.1f, %.1f)\t\n", triangle->p1.x, triangle->p1.y, triangle->p1.z);
		printf("Point 2 is at (%.1f, %.1f, %.1f)\t\n", triangle->p2.x, triangle->p2.y, triangle->p2.z);
		printf("Point 3 is at (%.1f, %.1f, %.1f)\t\n", triangle->p3.x, triangle->p3.y, triangle->p3.z);
		printf("RGB is (%d, %d, %d)\t", triangle->color.red, triangle->color.green, triangle->color.blue);
		printf("\n");
	}
}
