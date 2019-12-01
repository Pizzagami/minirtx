/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:32:33 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/01 20:04:36 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

#include "minirtx.h"

int				rgbtoon(t_color color);
int				ft_atoi(char *str, int x);
int				ft_strlen(char *str);
float      		ft_atof(char buf[BUFFER_SIZE], int x);
void			read_float(char buf[BUFFER_SIZE], int *x,float *ret);
int				second_degre(float a, float b, float c, float *x1, float *x2);
t_vec			min(t_vec truc, t_vec machin);
t_vec			normalize(t_vec vect);
t_vec			plus(t_vec truc, t_vec machin);
t_vec			fois(t_vec truc, float a);
t_vec			rotation(t_vec truc);
float			dot(t_vec machin, t_vec bidule);
void 			read_int(char buf[BUFFER_SIZE], int *x, int *ret);
char			*check_color(char buf[BUFFER_SIZE], int *x, t_color *color,char *str);
char			*join(char *s1, char *s2);
t_tg			*last_tg(t_tg *lst);
char			*check_vec(char buf[BUFFER_SIZE], int *x, t_vec *vec, char *id);
char			*check_pos(char buf[BUFFER_SIZE], int *x, t_vec *vec, char *id);

#endif
