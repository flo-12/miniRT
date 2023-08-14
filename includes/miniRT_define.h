/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:12 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/14 12:32:09 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H



/**************************************************************************
*                                MACROS                                   *
**************************************************************************/

# define THRESH_FLOAT 1e-6

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

# define COLOR_WHITE 0x00FFFFFF
# define COLOR_RED 0x00FF0000
# define COLOR_GREEN 0x0000FF00
# define COLOR_BLUE 0x000000FF


# define MSG_OPENFILE_ERROR "Cannot open file\n"
# define MSG_MLX_ERROR "MLX usage...\n"
# define MSG_MALLOC_ERROR "Malloc failed\n"
# define MSG_INPUT_ERROR "Syntax in file wrong - a line is missing information\n"
# define MSG_ARG_ERROR "Incorrect number of arguments - usage: \"./miniRT <inputFile>\"\n"
# define MSG_INPUT_INCOMPLETE "Input in file incomplete - ambient light, camera & light are required\n"
# define MSG_FILETYPE_ERROR "Wrong filetype - \"*.rt\" file required\n"


# ifndef DEBUG_RENDER
#  define DEBUG_RENDER 1
# endif

# ifndef DEBUG_PARSER
#  define DEBUG_PARSER 1
# endif
/**************************************************************************
*                                 ENUMS                                   *
**************************************************************************/

enum e_types {
	SPHERE,
	PLANE,
	CYLINDER
};

typedef enum e_exit_code {
	SUCCESS,
	OPENFILE_ERROR,
	MLX_ERROR,
	MALLOC_ERROR,
	INPUT_ERROR,
	ARG_ERROR,
	INPUT_INCOMPLETE,
	FILETYPE_ERROR
}	t_exit_code;

/**************************************************************************
*                               STRUCTURES                                *
**************************************************************************/

typedef struct s_pixel
{
	int	x;
	int	y;
}	t_pixel;

typedef struct s_coordinates
{
	float	x;
	float	y;
	float	z;
}	t_coordinates;

typedef struct s_vector
{
	t_coordinates	origin;
	t_coordinates	v_norm;
}	t_vector;

typedef struct s_hit
{
	t_coordinates	p1;
	t_coordinates	p2;
}	t_hit;

typedef struct s_colors // Q: include t value for put-pixel?
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_cylinder
{
	t_coordinates	*center;
	t_coordinates	*v_norm;
	float			d;
	float			h;
	t_color			*color;
}	t_cylinder;

typedef struct s_plane
{
	t_coordinates	*point;
	t_coordinates	*v_norm;
	t_color			*color;
}	t_plane;

typedef struct s_sphere
{
	t_coordinates	*center;
	float			d;
	t_color			*color;
}	t_sphere;

typedef struct s_light
{
	t_coordinates	*point;
	float			brightness;
	t_color			*color;
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	t_coordinates	*point;
	t_coordinates	*v_norm;
	float			fov;
	float 			focal_len;
	float			m[3][3];
}	t_camera;

typedef struct s_ambient
{
	float			ratio;
	t_color			*color;
}	t_ambient;

typedef struct s_object
{
	enum e_types	identifier;
	union
	{
		t_cylinder	cylinder;
		t_plane		plane;
		t_sphere	sphere;
	} u_obj;
	struct s_object	*next;
}	t_object;

typedef struct s__img {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_global
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_light		*light;
	t_camera	*camera;
	t_ambient	*ambient;
	t_object	*objects;
}	t_global;

#endif
