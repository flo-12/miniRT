/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:12 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/01 19:01:11 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

/**************************************************************************
*                                MACROS                                   *
**************************************************************************/

# define STR_ERR_ARG "error: a scene in format *.rt mus be entered \
(exactly one arg)"

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
	PARSE_ERROR,
	MLX_ERROR,
	MALLOC_ERROR,
} t_exit_code;

/**************************************************************************
*                               STRUCTURES                                *
**************************************************************************/

typedef struct s_coordinates
{
	float	x;	// maybe double, but float b/c faster
	float	y;
	float	z;
} t_coordinates;

typedef struct s_colors // Q: include t value for put-pixel?
{
	int	r;	// float or int?
	int	g;
	int	b;
} t_color;

typedef struct s_cylinder
{
	t_coordinates	center;
	t_coordinates	v_norm;
	float			d;
	float			h;
	t_color			color;
} t_cylinder;

typedef struct s_plane
{
	t_coordinates	point;
	t_coordinates	v_norm;
	t_color			color;
} t_plane;

typedef struct s_sphere
{
	t_coordinates	center;
	float			d;
	t_color			color;
} t_sphere;

typedef struct s_light
{
	t_coordinates	point;
	float			brightness;
	t_color			color;
	struct s_light	*next;
} t_light;

typedef struct s_camera
{
	t_coordinates	point;
	t_coordinates	v_norm;
	float			fov;
} t_camera;

typedef struct s_ambient
{
	t_coordinates	center;
	float			ratio;
	t_color			color;
} t_ambient;

typedef struct s_object
{
	enum e_types	identifier;
	union object
	{
		t_cylinder	cylinder;
		t_plane		plane;
		t_sphere	sphere;
	} u_obj;
	struct s_object	*next;
} t_object;

typedef struct s__img {
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;

typedef struct s_global
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_light		*light;
	t_camera	*camera;
	t_ambient	*ambient;
	t_object	*objects;
} t_global;


#endif
