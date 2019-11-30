/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:10:53 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/30 18:42:04 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRTX_H
# define MINIRTX_H

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 2147483
#define StructureNotifyMask	(1L<<17)
#define DestroyNotify	17

typedef struct	s_vec
{
	float x;
	float y;
	float z;
}				t_vec;

typedef struct 	color
{
	char	r;
	char	g;
	char	b;
}				t_color;

typedef struct	s_light
{
	t_vec	pos;
	t_color	color;
	void	*next;
}				t_light;

typedef struct	s_coor
{
	float x;
	float y;
}				t_coor;

typedef struct	s_cam
{
	t_vec origin;
	t_vec ray;
}				t_cam;

typedef	struct s_obj
{
	t_vec center;
	t_vec	p1;
	t_vec	p2;
	t_vec	p3;
	t_vec	vec;
	t_color	color;
	float	dia;
	float	hi;
	int		type;

}				t_tg;

typedef struct	s_amb
{
	t_color	color;
	float	ratio;	
}				t_amb;

typedef struct	s_res
{
	float x;
	float y;
}				t_res;

typedef struct	s_all
{
	t_res	res;
	t_amb	amb;
	t_vec	vec;
	t_color	color;
	t_coor	coor;
	t_cam	cam;
	t_light	*light;
	t_tg	*shape;
}				t_rtx;

t_rtx			parseke(char *str);
t_rtx			parsing(int fd);
t_color			cal_col(t_cam, t_tg shape, t_light l1);
t_vec			min(t_vec truc, t_vec machin);
t_vec			normalize(t_vec vect);
t_vec			plus(t_vec truc, t_vec machin);
t_vec			fois(t_vec truc, float a);
t_vec			rotation(t_vec truc);
float			dot(t_vec machin, t_vec bidule);
float			find_dist(t_cam, t_tg shape);
int				inter(t_vec	dot, t_vec center, float hi, t_vec vec);
int				second_degre(float a, float b, float c, float *x1, float *x2);
int				key_hook(int key);
int				exit_hook(void *param);
int				rgbtoon(t_color color);
int				ft_atoi(char *str);
char			*init_ar(char buf[BUFFER_SIZE], int *x, t_rtx *rtx);
char			*init_view(char buf[BUFFER_SIZE], int *x, t_rtx *rtx);
char			*init_sp(char buf[BUFFER_SIZE], int *x, t_rtx *rtx);
char			*init_tc(char buf[BUFFER_SIZE], int *x, t_rtx *rtx);
int				ft_strlen(char *str);
float      		ft_atof(char buf[BUFFER_SIZE], int x);

#endif