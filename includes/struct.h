/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:30:49 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/03 14:13:40 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
	t_vec	pos;
	t_color	color;
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
	int		fov;
	struct s_cam	*next;
}				t_cam;

typedef	struct s_obj
{
	t_vec	center;
	t_vec	p1;
	t_vec	p2;
	t_vec	p3;
	t_vec	vec;
	t_color	color;
	float	dia;
	float	hi;
	int		type;
	struct s_obj	*next;

}				t_tg;

typedef struct	s_amb
{
	t_color	color;
	float	ratio;	
}				t_amb;

typedef struct	s_res
{
	int x;
	int y;
}				t_res;

typedef struct	s_all
{
	t_res	res;
	t_amb	amb;
	t_vec	vec;
	t_color	color;
	t_coor	coor;
	t_cam	*cam;
	t_light	*light;
	t_tg	*shape;
}				t_rtx;

#endif