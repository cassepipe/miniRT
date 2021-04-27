/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:28 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/27 12:06:29 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

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
# include "defines.h"

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"

extern t_env	g_env;

void			check_args(int argc, char *argv[]);
void			check_rt_extension(char *filename);
t_vec3			new_vec3(double x, double y, double z);
t_vec3			canvas_to_viewport(int x, int y, double fov);
void			render_image_list(struct s_image *images);
t_color			trace_ray(t_ray *ray);
bool			intersect_ray_with_object(t_ray *ray, t_object *obj, double *t);
bool			intersect_ray_with_sphere(t_ray *ray, t_sphere *sph, double *t);
bool			intersect_ray_with_cylinder(t_ray *ray, t_cyl *cyl, double *t);
bool			intersect_ray_with_plane(t_ray *ray, t_plane *plane, double *t);
bool			intersect_ray_with_triangle(t_ray *ray, t_triangle *triangle,
																	double *t);
bool			intersect_ray_with_square(t_ray *ray, t_square *sq, double *t);
t_color			get_object_color(t_object *object);
int				get_color_as_int(t_color color);
t_vec3			sub_vec(t_vec3 point1, t_vec3 point2);
double			dot(t_vec3 u, t_vec3 v);
void			init_env();
void			create_images();
t_color			compute_ray_color(t_ray *ray, t_object *object, double t);
t_color			compute_sphere_lighting(t_ray *ray, t_sphere *sphere, double t);
t_color			compute_cylinder_lighting(t_ray *ray, t_cyl *cyl, double t);
t_color			compute_plane_lighting(t_ray *ray, t_plane *plane, double t);
t_color			compute_triangle_lighting(t_ray *ray, t_triangle *tr, double t);
t_color			compute_square_lighting(t_ray *ray, t_square *square, double t);
t_vec3			compute_lighting(t_vec3 hit_point, t_vec3 normal);
void			put_pixel_to_image(struct s_image *img, int x, int y, int colo);
double			vec_len(t_vec3	v);
bool			trace_light(t_ray *ray);
t_matrix3x3		compute_cam_to_world_matrix(t_vec3 camera_direction);
t_vec3			apply_rotation_to_ray(t_vec3 ray, t_matrix3x3 rot_matrix);

t_vec3			add_vec(t_vec3 v, t_vec3 w);
t_vec3			scale_by(t_vec3 vector, double scalar);
t_color			apply_lighting(t_color color, t_vec3 lighting);
t_vec3			distribute_colors(t_color color);
t_vec3			normalize(t_vec3 v);
t_vec3			new_vec3(double x, double y, double z);
t_vec3			make_vector_substracting_2_points(t_vec3 point1, t_vec3 point2);
t_vec3			cross_product(t_vec3 v1, t_vec3 v2);
double			autodot(t_vec3 v);

t_matrix3x3		transpose_mat3x3(t_matrix3x3 mat);
t_matrix3x3		invert_matrix3x3(t_matrix3x3 matrix);
t_vec3			mult_matrix3x3_vec3(t_matrix3x3 mat, t_vec3 v);

void			free_env(t_env *env);
void			free_object_list(t_object *objects);
void			free_light_list();
void			free_camera_list(t_cam *cameras);

int				handle_keypress(int keycode, void *params);
int				cleanup_and_quit();
void			create_bmp();

void			die();

#endif
