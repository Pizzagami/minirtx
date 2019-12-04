/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:32:33 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/04 13:16:56 by selgrabl         ###   ########.fr       */
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

t_vec			rotation(t_vec truc);
t_vec			normalize(t_vec vect);
t_vec			fois(t_vec truc, float a);
t_vec			min(t_vec truc, t_vec machin);
t_vec			plus(t_vec truc, t_vec machin);
t_color			lfois(t_color color, float a);
int				ft_strcmp(char *s1, char *s2);

#endif
