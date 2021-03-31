/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:52:48 by tpouget           #+#    #+#             */
/*   Updated: 2021/03/31 18:52:24 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_env	env;

void		init_env(t_env *env)
{
	env->objects = NULL;
	env->cameras = NULL;
	env->lights = NULL;
}

int			main(int argc, char *argv[])
{

	void *mlx_ptr;
	void *window;
	struct s_image image;

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
	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		die("Failed to set up connection to X server");
	window = mlx_new_window(mlx_ptr, env.res_x, env.res_y, "miniRT");

	image.mlx_handle = mlx_new_image(mlx_ptr, env.res_x, env.res_y);
	image.data = mlx_get_data_addr(image.mlx_handle, &image.bits_per_pixel, &image.line_len, &image.endianness);

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
				//printf("Processing pixel(%d, %d)...\n", x, y);
				ray = canvas_to_viewport(x, y);
				ray = normalize(ray);
				ray = apply_rotation_to_ray(ray, env.cameras->cam_to_world);
				closest_object_color = trace_ray(&env.cameras->origin, &ray);
				pixel_color = get_color_as_int(closest_object_color);
				put_pixel_to_image(&image, x, y, pixel_color);
				x++;
			}
			y++;
		}

	mlx_put_image_to_window(mlx_ptr, window, image.mlx_handle, 0, 0);
	mlx_loop(mlx_ptr);

	return (0);
}

double squareof(x)
{
	return (x*x);
}

t_matrix3x3		transpose_mat3x3(t_matrix3x3 mat)
{
	t_matrix3x3	result;

	result.right.x = mat.right.x;
	result.right.y = mat.up.x;
	result.right.z = mat.forward.x;
	result.up.x = mat.right.y;
	result.up.y = mat.up.y;
	result.up.z = mat.forward.y;
	result.forward.x = mat.right.z;
	result.forward.y = mat.up.z;
	result.forward.z = mat.forward.z;
	return (result);
}

t_matrix3x3		invert_matrix3x3(t_matrix3x3 matrix)
{
	t_matrix3x3	result;
	t_vec3		v_x;
	t_vec3		v_y;
	t_vec3		v_z;

	v_x = new_vec3(matrix.right.x, matrix.up.x, matrix.forward.x);
	v_x = scale_by(v_x, 1 / squareof(vec_len(v_x)));
	v_y = new_vec3(matrix.right.y, matrix.up.y, matrix.forward.y);
	v_y = scale_by(v_x, (1 / squareof(vec_len(v_y))));
	v_z = new_vec3(matrix.right.z, matrix.up.z, matrix.forward.z);
	v_z = scale_by(v_z, (1 / squareof(vec_len(v_z))));
	result.right = new_vec3(v_x.x, v_x.y, v_x.z);
	result.up = new_vec3(v_y.x, v_y.y, v_y.z);
	result.forward = new_vec3(v_z.x, v_z.y, v_z.z);
	return (result);
}

t_vec3			mult_matrix3x3_vec3(t_matrix3x3 mat, t_vec3 v)
{
	t_vec3		result;
	t_matrix3x3	tmp_mat;

	tmp_mat = transpose_mat3x3(mat);
	result.x = dot(tmp_mat.right, v);
	result.y = dot(tmp_mat.up, v);
	result.z = dot(tmp_mat.forward, v);
	return (result);
}

t_vec3	apply_rotation_to_ray(t_vec3 ray, t_matrix3x3 rot_matrix)
{
	t_vec3 result;

	/*result.x = ray.x*rot_matrix.right.x + ray.y*rot_matrix.right.y + ray.z*rot_matrix.right.z;
	result.y = ray.x*rot_matrix.up.x + ray.y*rot_matrix.up.y + ray.z*rot_matrix.up.z;
	result.z = ray.x*rot_matrix.forward.x + ray.y*rot_matrix.forward.y + ray.z*rot_matrix.forward.z;*/

	result = mult_matrix3x3_vec3(rot_matrix, ray);

	return (result);
}

t_matrix3x3	compute_cam_to_world_matrix(t_vec3 camera_direction)
{
	t_matrix3x3 result;

	result.forward = normalize(camera_direction);
	result.right = normalize(cross_product((struct s_vec3){0,1,0}, result.forward ));
	result.up = normalize(cross_product(result.forward, result.right));

	//result = invert_matrix3x3(result);

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
	double		parameter;
	double		previous_parameter;

	closest_object = NULL;
	current_object = env.objects;
	has_hit = false;
	parameter = INFINITY;
	previous_parameter = INFINITY;

	while (current_object != NULL)
	{
		//printf("Current object is %p\n", current_object);
		previous_parameter  = parameter;
		has_hit = intersect_ray_with_object(eye, ray, current_object, &parameter, 1, INFINITY);
		if (has_hit && parameter <= previous_parameter)
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

t_color	compute_ray_color(t_vec3 *ray, t_vec3 *eye, t_object *object, double parameter)
{
	if (object->id == SPHERE)
		return	(compute_sphere_lighting(ray, eye, (t_sphere*)(object->data), parameter));
	if (object->id == CYLINDER)
		return	(compute_cylinder_lighting(ray, eye, (t_cylinder*)(object->data), parameter));
	else
		die("Could not compute light: Unrecognized object type");
}

double 	compute_lighting(t_vec3 hit_point, t_vec3 normal)
{
	double	i;
	t_light *light;
	t_vec3	light_vector;
	double	n_dot_l;

	i = env.ambl_ratio;
	//printf("ambl ratio is %f\n", i);
	light = env.lights;
	while (light != NULL && i < 1)
	{
		light_vector = substract_vec3(light->origin, hit_point);

			n_dot_l = dot(light_vector, normal);
			if (n_dot_l > 0)
			{
				if (!trace_light(&hit_point, &light_vector))
					i += light->ratio * n_dot_l/(vec_len(normal) * vec_len(light_vector));
			}
		light = light->next;
	}
	if (i > 1)
		return (1);
	//printf("returning ratio %.1f\n", i);
	return (i);
}


t_color	compute_sphere_lighting(t_vec3 *ray, t_vec3 *eye, t_sphere *sphere, double parameter)
{
		t_vec3 hit_point;
		t_vec3 normal;

		hit_point = scale_by(*ray, parameter);
		hit_point = add_vec(*eye, hit_point);

		normal = substract_vec3(hit_point, sphere->center);  // Compute sphere normal at intersection
		normal = normalize(normal);

		return (scale_color_by(sphere->color, compute_lighting(hit_point, normal)));
}

t_color	compute_cylinder_lighting(t_vec3 *ray, t_vec3 *eye, t_cylinder *cylinder, double parameter)
{
		t_vec3 hit_point;
		t_vec3 normal;
		double m;
		t_vec3 CO;
		t_vec3 AC;
		t_vec3 CP;

		CO = substract_vec3(*eye, cylinder->base);

		hit_point = scale_by(*ray, parameter);
		hit_point = add_vec(*eye, hit_point);

		m = dot(*ray, cylinder->orientation) ;
		m = m * parameter;
		m = m + dot(CO, *ray);

		AC = scale_by(cylinder->orientation, -m);
		CP =  substract_vec3(hit_point, cylinder->orientation);

		normal = add_vec(AC, CP);
		normal = normalize(normal);

		return (scale_color_by(cylinder->color, compute_lighting(hit_point, normal)));
		return cylinder->color;
}

bool		intersect_ray_with_object(t_vec3 *eye, t_vec3 *ray, t_object *object, double *solution, double tmin, double tmax)
{
	if (object->id == SPHERE)
		return	(intersect_ray_with_sphere(eye, ray, (t_sphere*)(object->data), solution, tmin, tmax));
	if (object->id == CYLINDER)
	{
		return	(intersect_ray_with_cylinder(eye, ray, (t_cylinder*)(object->data), solution, tmin, tmax));
	}
	else
		die("Intersection impossible : Unrecognized object type");
	return (0);
}

bool		intersect_ray_with_sphere(t_vec3 * O,  t_vec3 *ray, t_sphere *sphere, double *solution,
										double tmin, double tmax)
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

	/*printf("For ray [%f, %f, %f]\n", ray->x, ray->y, ray->z);*/
	radius = sphere->diameter * 0.5;
	CO = substract_vec3(*O, sphere->center);

	a = dot(*ray, *ray);
	b = 2 * dot(CO, *ray);
	c = dot(CO, CO) - radius*radius;

	discriminant = b*b - 4*a*c;

	/*printf("discriminant = %f\n", discriminant);*/
	if (discriminant < 0)
	{
		return 0;
	}

	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);

	/*printf("t1 = %f\n\n", t1);*/
	/*printf("t2 = %f\n\n", t2);*/

	has_hit = false;
	if (t1 > tmin && t1 < tmax && t1 < *solution)
	{
		*solution = t1;
		has_hit = true;
	}
	if (t2 > tmin  && t2 < tmax && t2 < *solution)
	{
		*solution = t2;
		has_hit = true;
	}
	return (has_hit);
}

double	autodot(t_vec3 v)
{
	return (dot(v, v));
}

double sq(double value)
{
	return (value * value);
}

/*bool		intersect_ray_with_cylinder(t_vec3 * eye,  t_vec3 *ray, t_cylinder *cylinder, double *solution,*/
										/*double tmin, double tmax)*/
/*{*/
	/*double	radius;*/
	/*double	a;*/
	/*double	b;*/
	/*double	c;*/
	/*double z1;*/
	/*double z2;*/
	/*double zmin;*/
	/*double zmax;*/
	/*double	discriminant;*/
	/*double  t1;*/
	/*double  t2;*/
	/*double  t3;*/
	/*double  t4;*/
	/*t_vec3 CO;*/
	/*bool	has_hit;*/
	/*int	hit_caps;*/
	/*double DdotD;*/
	/*double DdotV;*/
	/*double DdotCO;*/
	/*double COdotCO;*/
	/*double COdotV;*/

	/*radius = cylinder->diameter * 0.5;*/

	/*//Normalizing*/
	/**ray = normalize(*ray);*/
	/*cylinder->orientation = normalize(cylinder->orientation);*/

	/*CO = substract_vec3(*eye, cylinder->base);*/

	/*DdotD = autodot(*ray);*/
	/*DdotV = dot(*ray, cylinder->orientation);*/
	/*DdotCO = dot(*ray, CO);*/
	/*COdotCO = autodot(CO);*/
	/*COdotV = dot(CO, cylinder->orientation);*/

	/*a = DdotD - sq(DdotV);*/

	/*b = 2 * DdotCO - DdotV * COdotV;*/

	/*c = COdotCO - sq(COdotV) - sq(radius);*/


	/*discriminant = b*b - 4*a*c;*/

	/*if (discriminant < 0)*/
	/*{*/
		/*return 0;*/
	/*}*/

	/*t1 = (-b + sqrt(discriminant)) / (2 * a);*/
	/*t2 = (-b - sqrt(discriminant)) / (2 * a);*/

	/*z1 = eye->z + t1 * ray->z;*/
	/*z2 = eye->z + t2 * ray->z;*/

	/*zmin = cylinder->base.z;*/
	/*zmax = cylinder->base.z + cylinder->orientation.z * cylinder->height; //Cylinder height does not necessarily correpond to z axis.*/

	/*has_hit = false;*/
	/*hit_caps = 0;*/
	/*//if ((z1 > zmin && z1 < zmax) || (z1 < zmin && z2 > zmax))*/
	/*{*/
		/*hit_caps++;*/
		/*if (t1 > tmin && t1 < tmax && t1 < *solution)*/
		/*{*/
			/**solution = t1;*/
			/*has_hit = true;*/
		/*}*/
	/*}*/
	/*//if ((z2 > zmin && z2 < zmax) || (z2 < zmin && z2 > zmax))*/
	/*{*/
		/*hit_caps++;*/
		/*if (t2 > tmin  && t2 < tmax && t2 < *solution)*/
		/*{*/
			/**solution = t2;*/
			/*has_hit = true;*/
		/*}*/
	/*}*/
	/*[>if (hit_caps == 1)<]*/
	/*[>{<]*/
		/*[>t3 = (zmin - eye->z) / ray->z;<]*/
		/*[>t4 = (zmax - eye->z) / ray->z;<]*/
		/*[>if (t3 > tmin && t3 < tmax && t3 < *solution)<]*/
		/*[>{<]*/
			/*[>*solution = t3;<]*/
			/*[>has_hit = true;<]*/
		/*[>}<]*/
		/*[>if (t4 > tmin && t4 < tmax && t4 < *solution)<]*/
		/*[>{<]*/
			/*[>*solution = t4;<]*/
			/*[>has_hit = true;<]*/
		/*[>}<]*/
	/*[>}<]*/

	/*return (has_hit);*/
/*}*/

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
		printf("Center is at (%.1f, %.1f, %.1f)\t", cyl->base.x, cyl->base.y, cyl->base.z);
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
