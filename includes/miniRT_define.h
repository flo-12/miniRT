/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:12 by fbecht            #+#    #+#             */
/*   Updated: 2023/08/01 15:41:14 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H

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

enum e_types {
	AMBIENT = 1,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
};

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
	e_types	identifier;
	union object	// check difference "union struct" and simply "union"
	{
		t_cylinder	*cylinder;
		t_plane		*plane;
		t_sphere	*sphere;
		t_light		*light;
		t_camera	*camera;
		t_ambient	*ambient;
	} obj;
	t_object	*next;
} t_object;

#endif
