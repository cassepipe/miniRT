#ifndef MINI_RT_H
# define MINI_RT_H

# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <stdio.h>
# include <ctype.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

# include "structs.h"
# include "parse.h"
# include "error.h"


# include "libft/libft.h"

extern t_env env;

void		prints(struct s_object*);
t_vec3		new_vec3(double x, double y, double z);
t_vec3		canvas_to_viewport(int x, int y);
t_color		trace_ray(t_vec3 *eye, t_vec3 *D);
bool		intersect_ray_with_object(t_vec3 *eye, t_vec3 *ray, t_object *object, double *solution, double tmin, double tmax);
bool		intersect_ray_with_sphere(t_vec3 *eye, t_vec3 *ray, t_sphere *sphere, double *solution, double tmin, double tmax);
bool		intersect_ray_with_cylinder(t_vec3 * O,  t_vec3 *ray, t_cylinder *sphere, double *solution,
										double tmin, double tmax);
t_color		get_object_color(t_object *object);
int			get_color_as_int(t_color color);
t_vec3		make_vector_substracting_2_points(t_vec3 point1, t_vec3 point2);
double		dot_product(t_vec3 u, t_vec3 v);
void		init_env(t_env *env);
t_color		compute_ray_color(t_vec3 *ray, t_vec3 *eye, t_object *object, double parameter);
t_color		compute_sphere_lighting(t_vec3 *ray, t_vec3 *eye, t_sphere *sphere, double parameter);
double		compute_lighting(t_vec3 hit_point, t_vec3 normal);
void		put_pixel_to_image(struct s_image *image, int x, int y, int color);
double		vec_len(t_vec3	v);
bool		trace_light(t_vec3 *origin, t_vec3 *ray);
t_matrix3x3	compute_cam_to_world_matrix(t_vec3 camera_direction);
t_vec3		apply_rotation_to_ray(t_vec3 ray, t_matrix3x3 rot_matrix);

t_vec3	scale_by(t_vec3 vector, double scalar);
t_color	scale_color_by(t_color color, double scalar);
t_vec3	add_vec(t_vec3 v1, t_vec3 v2);
t_vec3	normalize(t_vec3 v);
t_vec3	new_vec3(double x, double y, double z);
t_vec3	make_vector_substracting_2_points(t_vec3 point1, t_vec3 point2);
double	dot_product(t_vec3 u, t_vec3 v);
t_vec3	cross_product(t_vec3 v1, t_vec3 v2);

#endif
