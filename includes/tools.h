/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:32:33 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/06 17:08:52 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

#include "minirtx.h"

int				ft_strlen(char *str);
int				rgbtoon(t_color color);
int				ft_atoi(char *str, int x);
int				second_degre(float a, float b, float c, float *x1, float *x2);

char			*join(char *s1, char *s2);
char			*read_vec(char buf[BUFFER_SIZE], int *x, t_vec *vec, char *id);
char			*read_pos(char buf[BUFFER_SIZE], int *x, t_vec *vec, char *id);
char			*read_color(char buf[BUFFER_SIZE], int *x,
				t_color *color,char *str);

float			dot(t_vec machin, t_vec bidule);
float      		ft_atof(char buf[BUFFER_SIZE], int x);

void			init_lst(int fd, t_rtx *rtx);
int 			read_int(char buf[BUFFER_SIZE], int *x);
float			read_float(char buf[BUFFER_SIZE], int *x);

t_vec			xfois(t_vec truc, float a);
t_vec			normalize(t_vec vect);
t_vec			fois(t_vec truc, float a);
t_vec			min(t_vec truc, t_vec machin);
t_vec			plus(t_vec truc, t_vec machin);
t_vec			cross(t_vec machin, t_vec bidule);
t_color			lfois(t_color color, float a);
t_color			color_add(t_color base, t_color add, float coef);
t_color			color_cap(t_color color, t_color max);
int				ft_strcmp(char *s1, char *s2);
float			find_dist(t_vec origin, t_vec ray, t_tg shape);

#endif
