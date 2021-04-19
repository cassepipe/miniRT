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
# include <stdint.h>

# include "structs.h"
# include "parse.h"
# include "error.h"
# include "defines.h"

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"

extern t_env env;


void		prints(struct s_object*);
t_vec3		new_vec3(double x, double y, double z);
t_vec3		canvas_to_viewport(int x, int y);
t_color		trace_ray(t_vec3 *eye, t_vec3 *D);
bool		intersect_ray_with_object(t_vec3 *eye, t_vec3 *ray, t_object *object, double *solution, double tmin, double tmax);
bool		intersect_ray_with_sphere(t_vec3 *eye, t_vec3 *ray, t_sphere *sphere, double *solution, double tmin, double tmax);
bool		intersect_ray_with_cylinder(t_vec3 *eye, t_vec3 *ray, t_cylinder *cylinder, double *t, double tmin, double tmax);
bool		intersect_ray_with_plane(t_vec3 *eye, t_vec3 *ray, t_plane *plane, double *t, double tmin, double tmax);
bool		intersect_ray_with_triangle(t_vec3 *eye, t_vec3 *ray, t_triangle *triangle, double *t, double tmin, double tmax);
bool 		intersect_ray_with_square(t_vec3 *eye, t_vec3 *ray, t_square *square, double *t, double tmin, double tmax);
t_color		get_object_color(t_object *object);
int			get_color_as_int(t_color color);
t_vec3		substract_vec3(t_vec3 point1, t_vec3 point2);
double		dot(t_vec3 u, t_vec3 v);
void		init_env();
void		create_images();
t_color		compute_ray_color(t_vec3 *ray, t_vec3 *eye, t_object *object, double parameter);
t_color		compute_sphere_lighting(t_vec3 *ray, t_vec3 *eye, t_sphere *sphere, double parameter);
t_color		compute_cylinder_lighting(t_vec3 *ray, t_vec3 *eye, t_cylinder *cylinder, double parameter);
t_color		compute_plane_lighting(t_vec3 *ray, t_vec3 *eye, t_plane *plane, double parameter);
t_color		compute_triangle_lighting(t_vec3 *ray, t_vec3 *eye, t_triangle *triangle, double parameter);
t_color		compute_square_lighting(t_vec3 *ray, t_vec3 *eye, t_square *square, double parameter);
t_vec3		compute_lighting(t_vec3 hit_point, t_vec3 normal);
void		put_pixel_to_image(struct s_image *image, int x, int y, int color);
double		vec_len(t_vec3	v);
bool		trace_light(t_vec3 *origin, t_vec3 *ray);
t_matrix3x3	compute_cam_to_world_matrix(t_vec3 camera_direction);
t_vec3		apply_rotation_to_ray(t_vec3 ray, t_matrix3x3 rot_matrix);

t_vec3	add_vec(t_vec3 v, t_vec3 w);
t_vec3	scale_by(t_vec3 vector, double scalar);
t_color	apply_lighting(t_color color, t_vec3 lighting);
t_vec3	distribute_colors(t_color color);
t_vec3	normalize(t_vec3 v);
t_vec3	new_vec3(double x, double y, double z);
t_vec3	make_vector_substracting_2_points(t_vec3 point1, t_vec3 point2);
t_vec3	cross_product(t_vec3 v1, t_vec3 v2);
double	sq(double value);
double	autodot(t_vec3 v);

t_matrix3x3		transpose_mat3x3(t_matrix3x3 mat);
t_matrix3x3		invert_matrix3x3(t_matrix3x3 matrix);
t_vec3			mult_matrix3x3_vec3(t_matrix3x3 mat, t_vec3 v);

void free_env(t_env *env);
void free_object_list(t_object *objects);
void free_light_list();
void free_camera_list(t_cam *cameras);

int		handle_keypress(int keycode, void *params);
int		cleanup_and_quit();
void	create_bmp();

#endif
