#include "minirt.h"

t_env	env;

void prints(struct s_object*);
t_vec3 new_vec3(double x, double y, double z);
t_vec3 CanvasToViewport(int x, int y);
t_object	*trace_ray( t_vec3 eye, t_vec3 D);
int intersect_ray_with_object(t_vec3 eye, t_vec3 ray, t_object *object);
int intersect_ray_with_sphere(t_vec3 eye, t_vec3 ray, t_sphere *sphere);
t_color get_object_color( t_object *object);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		perror("You have not provided any arguments");
		return (0);
	}

	env.scene_path = argv[1];

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
	mlx_new_window(mlx_ptr, env.res_x, env.res_y, "miniRT");

	//Rendering

	t_vec3 ray;
	t_object *closest_object;
	t_color closest_color;
	int color;
	int Cw = 800;
	int Ch = 800;
	int x = -Cw/2;
		while ( x <= Cw/2)
		{
			int y = -Ch/2;
			while (y <= Ch/2)
			{
				ray = CanvasToViewport(x, y);
					closest_object = trace_ray(env.cameras->origin, ray);
					closest_color = get_object_color(closest_object);
					color = get_color_as_int(closest_color);
					mlx_pixel_put(mlx_ptr, window,x, y, color);
			}
		}

	return (0);
}

int get_color_as_int(t_color *color)
{
	int color_int;
	int red;
	int green;
	int blue;

	red = (color->x) << 16;
	green = (color->y) << 8;
	blue = (color->z);

	color_int = red + green + blue;

	return (color_int);
}

t_vec3 CanvasToViewport(int x, int y)
{
	t_vec3 ray;
	int Cw = 800;
	int Ch = 800;
	int Vh = 1;
	int Vw = 1;

	ray.x = x * Vw/Cw;
	ray.y = y * Vh/Ch;
	ray.z = 1;

	return (ray);
}

t_object	*TraceRay( t_vec3 eye, t_vec3 ray)
{
	t_object *closest_object = NULL;
	t_object *current_object = env.objects;

	while (current_object != NULL)
	{
		double t1;
		current_object = env.objects;

		t1  = intersect_ray_with_object(eye, ray, current_object);
		if (t1 >= 1 && t1 < INT_MAX)
			closest_object = current_object;
		current_object = current_object->next;
	}
	if (closest_object == NULL)
	{
		return NULL;
	}
	return closest_object;
}

int intersect_ray_with_object(t_vec3 eye, t_vec3 ray, t_object *object)
{
	if (object->id == SPHERE)
		return	(intersect_ray_with_sphere(eye, ray, (t_sphere*)(object->data)));
	else
		die("Intersection impossible : Unrecognized object type");
	return (0);
}

t_color get_obj_color( t_object *object)
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
	return ((struct s_vec3) {0, 0, 0});
}


t_vec3 new_vec3(double x, double y, double z)
{
	t_vec3 vector;
	vector.x = 0;
	vector.y = 0;
	vector.z = 0;

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
		printf("RGB is (%.1f, %.1f, %.1f)\t", square->color.x, square->color.y, square->color.z);
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
		printf("RGB is (%.1f, %.1f, %.1f)\t", cyl->color.x, cyl->color.y, cyl->color.z);
		printf("\n");
	}
	else if (object->id == PLANE)
	{
		t_plane* plane;
		plane = object->data;

		printf("Plane:\t\t");
		printf("Point is at (%.1f, %.1f, %.1f)\t", plane->some_point.x, plane->some_point.y, plane->some_point.x);
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", plane->orientation.x, plane->orientation.y, plane->orientation.z);
		printf("RGB is (%.1f, %.1f, %.1f)\t", plane->color.x, plane->color.y, plane->color.z);
		printf("\n");
	}
}
