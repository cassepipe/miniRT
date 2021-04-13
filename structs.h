#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>

typedef struct s_vec3 {
	double x;
	double y;
	double z;
} t_vec3;

typedef struct s_color {
	int red;
	int green;
	int blue;
} t_color;

typedef struct s_matrix3x3 {
	t_vec3 forward;
	t_vec3 right;
	t_vec3 up;
} t_matrix3x3;

typedef struct s_quaternion {
	double a;
	double b;
	double c;
	double k;
} t_quaternion;

typedef struct s_ray {
	t_vec3		dir;
} t_ray;

typedef struct s_viewplane {
	double 		center;
	double		height;
	double		width;
} t_viewplane;

typedef struct s_cam {
	t_vec3			origin;
	t_vec3			direction;
	double			fov;
	t_matrix3x3		cam_to_world;
	struct s_cam	*next;
} t_cam;

typedef struct		s_light {
	t_vec3			origin;
	double			intensity;
	t_color			color;
	t_vec3			color_distribution;
	struct s_light *next;
}					t_light;

enum e_objid {
	CYLINDER,
	PLANE,
	SPHERE,
	SQUARE,
	TRIANGLE,
};

typedef struct s_object {
	enum e_objid	id;
	void 			*data;
	void		 	*next;
} t_object;

typedef	struct s_sphere {
	t_vec3		center;
	double		diameter;
	t_color		color;
} t_sphere;

typedef	struct s_plane {
	t_vec3		some_point;
	t_vec3		normal;
	t_color		color;
} t_plane;

typedef	struct s_square {
	t_vec3		center;
	t_vec3		dir;
	double		side_len;
	t_color		color;
} t_square;

typedef	struct s_cylinder {
	t_vec3		base;
	t_vec3		dir;
	double		diameter;
	double		height;
	t_color		color;
} t_cylinder;

typedef	struct s_triangle {
	t_vec3		p1;
	t_vec3		p2;
	t_vec3		p3;
	t_vec3		normal;
	t_color		color;
} t_triangle;

typedef struct s_env
{
	void				*mlx_session;
	void				*window;
	char				*scene_path;	
	int					number_of_cams;
	int					res_x;
	int					res_y;
	double				ambl_intensity;
	t_color				ambl_color;
	t_vec3				ambl_distrib;
	struct s_light		*lights;
	struct s_cam		*cameras;
	struct s_image		*images;
	struct s_image		*displayed_image;
	struct s_object		*objects;
} t_env;

struct s_fat_token {
	const char	*token;
	size_t		len;
	void		(*token_func)(char** input);
};

struct s_image {
	void			*mlx_handle;
	char			*data;
	t_cam			*cam;
	int				bits_per_pixel;
	int				line_len;
	int				endianness;
	struct 	s_image	*next;
}	t_image;


#endif
