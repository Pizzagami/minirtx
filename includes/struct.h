/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:30:49 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/25 15:19:02 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <pthread.h>

typedef struct	s_vec
{
	float x;
	float y;
	float z;
}				t_vec;

typedef struct 	s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_light
{
	float	ratio;
	t_vec	pos;
	t_color	color;
	t_vec	para;
	struct s_light	*next;
}				t_light;

typedef struct	s_coor
{
	float x;
	float y;
}				t_coor;

typedef struct	s_cam
{
	t_vec	origin;
	t_vec	ray;
	t_vec	vec;
	t_vec	up;
	t_vec	right;
	t_vec	rot;
	char	*id;
	void	*img;
	int		fov;
	int		num;
	char	filter;
	struct s_cam	*next;
}				t_cam;

typedef struct	s_res
{
	int x;
	int y;
}				t_res;

typedef	struct s_obj
{
	t_vec	center;
	t_vec	p1;
	t_vec	p2;
	t_vec	p3;
	t_vec	p4;
	t_vec	vec;
	t_vec	v1;
	t_vec	v2;
	t_vec	normal;
	t_color	color;
	int		type;
	float	dia;
	float	dam;
	float	hi;
	float	refl;
	float	trans;
	char	*map_id;
	t_res	map_res;
	struct s_obj	*next;

}				t_tg;

typedef struct	s_amb
{
	t_color	color;
	float	ratio;	
}				t_amb;

typedef struct	s_nor
{
	t_vec	norm;
	float	dist;
}				t_nor;

typedef struct	s_all
{
	t_res	res;
	t_nor	nor;
	t_amb	amb;
	t_vec	vec;
	t_color	color;
	t_coor	coor;
	t_cam	*cam;
	t_light	*light;
	t_tg	*shape;
	float	ar;
	float	aa;
	int		save;
	int		cam_num;
	void	*mlx_ptr;
	void	*mlx_win;
}				t_rtx;

typedef struct	s_matrix
{
	t_vec	a;
	t_vec	b;
	t_vec	c;
}				t_matrix;

typedef struct		s_send
{
	int				i;
	char			*id;
	void			*img;
	int				tiny_x;
	t_rtx			rtx;
}					t_send;

typedef struct		s_thread
{
	int				i;
	pthread_mutex_t *mutex;
	t_rtx			rtx;
	t_cam			cam;
}					t_thread;

#endif

/*	0 = plan 
	1 = sphere
	2 = cylindre
	3 = triangle
	4 = carre
	5 = pyramide
	6 = cube
	7 = cercle
	11 = shere with mapping (sm)
	123 = gauch
	124 = droite
*/