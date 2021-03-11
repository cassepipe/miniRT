#include "minirt.h"

t_env	env;

void		prints(struct s_object*);
t_vec3		new_vec3(double x, double y, double z);
t_vec3		canvas_to_viewport(int x, int y);
t_object	*trace_ray(t_vec3 *eye, t_vec3 *D);
bool		intersect_ray_with_object(t_vec3 *eye, t_vec3 *ray, t_object *object);
bool		intersect_ray_with_sphere(t_vec3 *eye, t_vec3 *ray, t_sphere *sphere);
t_color		*get_object_color(t_object *object);
int			get_color_as_int(t_color *color);
t_vec3		make_vector_substracting_2_points(t_vec3 point1, t_vec3 point2);
double		dot_product(t_vec3 u, t_vec3 v);
void		init_env(t_env *env);

void		init_env(t_env *env)
{
	env->objects = NULL;
	env->cameras = NULL;
	env->lights = NULL;
}

int			main(int argc, char *argv[])
{
	if (argc != 2)
	{
		perror("You have not provided any arguments");
		return (0);
	}

	env.scene_path = argv[1];

	init_env(&env);
	parse_file_into_env();

	struct s_object *cur = env.objects;
	while (cur)
	{
		prints(cur);
		cur = cur->next;
	}

	//minilibx
	void *mlx_ptr;
	void *window;
	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		die("Failed to set up connection to X server");
	window = mlx_new_window(mlx_ptr, env.res_x, env.res_y, "miniRT");

	//Rendering

	t_vec3 ray;
	t_object *closest_object;
	t_color *closest_object_color;
	int pixel_color;
		int y = 0;
		while ( y <= env.res_y)
		{
			int x = 0;
			while (x <= env.res_x)
			{
				/*printf("Processing pixel(%d, %d)...\n", x, y);*/
				ray = canvas_to_viewport(x, y);
				closest_object = trace_ray(&env.cameras->origin, &ray);
				/*printf("closest object is %p\n", closest_object);*/
				closest_object_color = get_object_color(closest_object);
				pixel_color = get_color_as_int(closest_object_color);
				mlx_pixel_put(mlx_ptr, window, x, y, pixel_color);
				x++;
			}
			y++;
		}

	mlx_loop(mlx_ptr);

	return (0);
}

int			get_color_as_int(t_color *color)
{
	int color_int;

	if (color == NULL)
		return (0xFFFFFF);
	color_int = color->red << 16 |  color->green << 8 | color->blue;

	return (color_int);
}

t_vec3		canvas_to_viewport(int x, int y)
{
	t_vec3 ray;

	ray.x = -env.res_x * 0.5 + x;
	ray.y = env.res_y * 0.5 - y;
	ray.z = 1;

	/*printf("Corresponding to viewport coordinates (%f,%f)\n", ray.x, ray.y);*/

	return (ray);
}

t_object	*trace_ray(t_vec3 *eye, t_vec3 *ray)
{
	t_object	*closest_object = NULL;
	t_object	*current_object = env.objects;
	bool		has_hit;

	has_hit = false;
	while (current_object != NULL)
	{
		has_hit = intersect_ray_with_object(eye, ray, current_object);
		if (has_hit)
		{
			closest_object = current_object;
		}
		current_object = current_object->next;
	}
	return closest_object;
}

bool		intersect_ray_with_object(t_vec3 *eye, t_vec3 *ray, t_object *object)
{
	if (object->id == SPHERE)
		return	(intersect_ray_with_sphere(eye, ray, (t_sphere*)(object->data)));
	else
		die("Intersection impossible : Unrecognized object type");
	return (0);
}

bool		intersect_ray_with_sphere(t_vec3 *eye,  t_vec3 *ray, t_sphere *sphere)
{
	double	radius;
	t_vec3	Ceye;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double  t1;
	double  t2;

	radius = sphere->diameter * 0.5;
	Ceye = make_vector_substracting_2_points(*eye, sphere->center);

	a = dot_product(*ray, *ray);
	b = 2 * dot_product(Ceye, *ray);
	c = dot_product(Ceye, Ceye) - radius*radius;

	discriminant = b*b - 4*a*c;
	if (discriminant < 0)
	{
		return 0;
	}
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);

	if ((1 < t1 && t1 < INFINITY ) || (1 < t2 && t2 < INFINITY))
		return (1);
	else
		return (0);

}

t_vec3		make_vector_substracting_2_points(t_vec3 point1, t_vec3 point2)
{
	t_vec3 vector;

	vector.x = point2.x - point1.x;
	vector.y = point2.y - point1.y;
	vector.z = point2.z - point1.z;

	return vector;

}

double dot_product(t_vec3 u, t_vec3 v)
{

	return (u.x * v.x + u.y * v.y +  u.z * v.z);
}

t_color *get_object_color(t_object *object)
{
	if (object == NULL)
		return (NULL);
	if (object->id == SPHERE)
		return &((t_sphere*)object->data)->color;
	if (object->id == CYLINDER)
		return &((t_sphere*)object->data)->color;
	if (object->id == SQUARE)
		return &((t_sphere*)object->data)->color;
	if (object->id == PLANE)
		return &((t_sphere*)object->data)->color;
	if (object->id == TRIANGLE)
		return &((t_sphere*)object->data)->color;
	die("Wrong object id while in get_obj_color");
	return (NULL);
}


t_vec3 new_vec3(double x, double y, double z)
{
	t_vec3 vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;

	return (vector);
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
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", square->orientation.x, square->orientation.y, square->orientation.z);
		printf("Side lenght is %.1f\t", square->side_len);
		printf("RGB is (%d, %d, %d)\t", square->color.red, square->color.green, square->color.blue);
		printf("\n");
	}
	else if (object->id == CYLINDER)
	{
		t_cylinder* cyl;
		cyl = object->data;

		printf("Cylinder:\t");
		printf("Center is at (%.1f, %.1f, %.1f)\t", cyl->center.x, cyl->center.y, cyl->center.x);
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", cyl->orientation.x, cyl->orientation.y, cyl->orientation.z);
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
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", plane->orientation.x, plane->orientation.y, plane->orientation.z);
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
}
