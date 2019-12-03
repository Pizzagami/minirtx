/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:32:33 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/03 15:41:34 by braimbau         ###   ########.fr       */
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
char			*check_vec(char buf[BUFFER_SIZE], int *x, t_vec *vec, char *id);
char			*check_pos(char buf[BUFFER_SIZE], int *x, t_vec *vec, char *id);
char			*check_color(char buf[BUFFER_SIZE], int *x,
				t_color *color,char *str);

float			dot(t_vec machin, t_vec bidule);
float      		ft_atof(char buf[BUFFER_SIZE], int x);

void			init_lst(int fd, t_rtx *rtx);
int 			read_int(char buf[BUFFER_SIZE], int *x);
float			read_float(char buf[BUFFER_SIZE], int *x);

t_tg			*last_tg(t_tg *lst);
t_cam			*last_cam(t_cam *lst);
t_vec			rotation(t_vec truc);
t_vec			normalize(t_vec vect);
t_vec			fois(t_vec truc, float a);
t_vec			min(t_vec truc, t_vec machin);
t_vec			plus(t_vec truc, t_vec machin);
t_light			*last_light(t_light *lst);

#endif
