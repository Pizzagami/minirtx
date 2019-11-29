/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:10:53 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/29 15:16:21 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRTX_H
# define MINIRTX_H

#include <mlx.h>
#include <math.h>
#include <stdio.h>

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
	int r;
	int g;
	int b;
}				t_color;

typedef struct	s_light
{
	t_vec	pos;
	t_color	color;
	void	*next;
}				t_light;

typedef struct	s_coor
{
	int res_x;
	int res_y;
	float x;
	float y;
}				t_coor;

typedef struct	s_cam
{
	t_vec origin;
	t_vec ray;
}				t_cam;

typedef	struct s_tg
{
	t_vec center;
	t_vec p1;
	t_vec p2;
	t_vec p3;
	t_vec vec;
	t_color color;
	float dia;
	float hi;

}				t_tg;


t_color			cal_col(t_cam, t_tg shape, t_light l1);
t_vec			min(t_vec truc, t_vec machin);
t_vec			normalize(t_vec vect);
t_vec			plus(t_vec truc, t_vec machin);
t_vec			fois(t_vec truc, float a);
float			dot(t_vec machin, t_vec bidule);
float			find_dist(t_cam, t_tg shape);
int				second_degre(float a, float b, float c, float *x1, float *x2);
int				key_hook(int key);
int				exit_hook(void *param);
int				rgbtoon(t_color color);
int				ft_atoi(char *str);

#endif