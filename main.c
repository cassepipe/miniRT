#include "minirt.h"

t_env	env;

void		prints(struct s_object*);
t_vec3		new_vec3(double x, double y, double z);
t_vec3		canvas_to_viewport(int x, int y);
t_color		trace_ray(t_vec3 *eye, t_vec3 *D);
bool		intersect_ray_with_object(t_vec3 *eye, t_vec3 *ray, t_object *object, double *solution);
bool		intersect_ray_with_sphere(t_vec3 *eye, t_vec3 *ray, t_sphere *sphere, double *solution);
t_color		get_object_color(t_object *object);
int			get_color_as_int(t_color color);
t_vec3		make_vector_substracting_2_points(t_vec3 point1, t_vec3 point2);
double		dot_product(t_vec3 u, t_vec3 v);
void		init_env(t_env *env);
t_color		compute_ray_color(t_vec3 *ray, t_vec3 *eye, t_object *object, double parameter);
t_color		compute_sphere_lighting(t_vec3 *ray, t_vec3 *eye, t_sphere *sphere, double parameter);
double		compute_lighting(t_vec3 hit_point, t_vec3 normal);

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
	t_color closest_object_color;
	int pixel_color;
		int y = 0;
		while ( y <= env.res_y)
		{
			int x = 0;
			while (x <= env.res_x)
			{
				printf("Processing pixel(%d, %d)...\n", x, y);
				ray = canvas_to_viewport(x, y);
				closest_object_color = trace_ray(&env.cameras->origin, &ray);
				pixel_color = get_color_as_int(closest_object_color);
				mlx_pixel_put(mlx_ptr, window, x, y, pixel_color);
				x++;
			}
			y++;
		}

	mlx_loop(mlx_ptr);

	return (0);
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
	double		parameter;

	closest_object = NULL;
	current_object = env.objects;
	has_hit = false;
	while (current_object != NULL)
	{
		printf("Current object is %p\n", current_object);
		has_hit = intersect_ray_with_object(eye, ray, current_object, &parameter);
		if (has_hit)
		{
			closest_object = current_object;
		}
		current_object = current_object->next;
	}
	if (closest_object == NULL)
		return (struct s_color){255,255,255};

	/*return get_object_color(closest_object);*/
	return compute_ray_color(ray, eye, closest_object, parameter);
}

t_color	compute_ray_color(t_vec3 *ray, t_vec3 *eye, t_object *object, double parameter)
{
	if (object->id == SPHERE)
		return	(compute_sphere_lighting(ray, eye, (t_sphere*)(object->data), parameter));
	else
		die("Could not compute light: Unrecognized object type");
}

t_vec3	scale_by(t_vec3 vector, double scalar)
{
	t_vec3 result;

	result.x = vector.x * scalar;
	result.y = vector.y * scalar;
	result.z = vector.z * scalar;

	return (result);
}

t_color	scale_color_by(t_color color, double scalar)
{
	t_color result;

	result.red = color.red * scalar;
	result.green = color.green * scalar;
	result.blue = color.blue * scalar;

	return (result);
}

t_vec3	add_vec(t_vec3 v1, t_vec3 v2)
{
	t_vec3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return (result);
}

double	vec_len(t_vec3	v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

t_vec3 normalize(t_vec3 v)
{
	double len;
	t_vec3 result;

	len = vec_len(v);

	result.x = v.x / len;
	result.y = v.y / len;
	result.z = v.z / len;

	return (result);
}

double 	compute_lighting(t_vec3 hit_point, t_vec3 normal)
{
	double	i;
	t_light *light;
	t_vec3	light_vector;
	double	n_dot_l;

	i = env.ambl_ratio;
	printf("ambl ratio is %f\n", i);
	light = env.lights;
	while (light != NULL && i < 1)
	{
		light_vector = make_vector_substracting_2_points(light->origin, hit_point);

			n_dot_l = dot_product(light_vector, normal);
			if (n_dot_l > 0)
			{
				i += light->ratio * n_dot_l/(vec_len(normal) * vec_len(light_vector));
			}
		light = light->next;
	}
	if (i > 1)
		return (1);
	printf("returning ratio %.1f\n", i);
	return (i);
}


t_color	compute_sphere_lighting(t_vec3 *ray, t_vec3 *eye, t_sphere *sphere, double parameter)
{
		t_vec3 hit_point;
		t_vec3 normal;

		hit_point = scale_by(*ray, parameter);
		hit_point = add_vec(*eye, hit_point);

		normal = make_vector_substracting_2_points(hit_point, sphere->center);  // Compute sphere normal at intersection
		normal = normalize(normal);

		return (scale_color_by(sphere->color, compute_lighting(hit_point, normal)));
}

bool		intersect_ray_with_object(t_vec3 *eye, t_vec3 *ray, t_object *object, double *solution)
{
	if (object->id == SPHERE)
		return	(intersect_ray_with_sphere(eye, ray, (t_sphere*)(object->data), solution));
	else
		die("Intersection impossible : Unrecognized object type");
	return (0);
}

bool		intersect_ray_with_sphere(t_vec3 * O,  t_vec3 *ray, t_sphere *sphere, double *solution)
{
	double	radius;
	t_vec3	CO;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double  t1;
	double  t2;
	bool	has_hit;

	printf("For ray [%f, %f, %f]\n", ray->x, ray->y, ray->z);
	radius = sphere->diameter * 0.5;
	CO = make_vector_substracting_2_points(*O, sphere->center);

	a = dot_product(*ray, *ray);
	b = 2 * dot_product(CO, *ray);
	c = dot_product(CO, CO) - radius*radius;

	discriminant = b*b - 4*a*c;

	printf("discriminant = %f\n", discriminant);
	if (discriminant < 0)
	{
		return 0;
	}

	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);

	printf("t1 = %f\n\n", t1);
	printf("t2 = %f\n\n", t2);

	has_hit = false;
	if (t1 > 1 && t1 < INFINITY)
	{
		*solution = t1;
		has_hit = true;
	}
	if (t2 > 1  && t2 < INFINITY && t2 < *solution)
	{
		*solution = t2;
		has_hit = true;
	}
	return (has_hit);
}

t_vec3		make_vector_substracting_2_points(t_vec3 point1, t_vec3 point2)
{
	t_vec3 vector;

	vector.x = point1.x - point2.x;
	vector.y = point1.y - point2.y;
	vector.z = point1.z - point2.z;

	return vector;

}

double dot_product(t_vec3 u, t_vec3 v)
{

	return (u.x * v.x + u.y * v.y +  u.z * v.z);
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
