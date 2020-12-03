#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>

typedef struct s_vec3 {
	double x;
	double y;
	double z;
} t_vec3;

typedef t_vec3 t_color;

typedef double t_matrix3x3[3][3];
typedef double t_matrix4x4[4][4];

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
	struct s_cam	*next;
} t_cam;

typedef struct		s_light {
	t_vec3			origin;
	double			ratio;
	t_color			color;
	struct s_light *next;
}					t_light;

enum e_objid {
	CYLINDER,
	PLANE,
	SPHERE,
	SQUARE,
	TRIANGLE,
};

typedef struct s_node {
	enum e_objid	id;
	void 			*object;
	void		 	*next;
} t_node;

typedef	struct s_sphere {
	t_vec3		center;
	double		diameter;
	t_color		color;
} t_sphere;

typedef	struct s_plane {
	t_vec3		some_point;
	t_vec3		orientation;
	t_color		color;
	void		*next;
} t_plane;

typedef	struct s_square {
	t_vec3		center;
	t_vec3		orientation;
	double		side_len;
	t_color		color;
} t_square;

typedef	struct s_cylinder {
	t_vec3		center;
	t_vec3		orientation;
	double		diameter;
	double		height;
	t_color		color;
} t_cylinder;

typedef	struct s_triangle {
	t_vec3		p1;
	t_vec3		p2;
	t_vec3		p3;
	t_color		color;
} t_triangle;

typedef struct s_env
{
	char				*scene_path;	
	int					res_x;
	int					res_y;
	int					ambl_ratio;
	t_color				ambl_color;
	struct s_light		*lights;
	struct s_cam		*cameras;
	struct s_node		*objects;
} t_env;

struct s_fat_token {
	const char	*token;
	size_t		len;
	void		(*token_func)(char** input);
};

#endif
