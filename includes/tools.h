/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:32:33 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/12 13:32:46 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

#include "minirtx.h"

int				ft_strlen(char *str);
int				rgbtoon(t_color color);
int				ft_atoi(char *str);
int     		distri(t_tg tri, t_vec p);
int				ft_strcmp(char *s1, char *s2);
int				second_degre(float a, float b, float c, float *x1, float *x2);
int     		distsqr(t_vec   dot, t_vec center, float hi, t_vec vec, t_rtx rtx);

char			*check_ligne(char *str);
char			*join(char *s1, char *s2);
char			*ultimate_join(int nbr, char *s1, ...);
char			*read_vec(char *buf, t_vec *vec, char *id);
char			*read_pos(char *buf, t_vec *vec, char *id);
char			*read_color(char *buf, t_color *color,char *str);

float      		ft_atof(char *buf);
float			dot(t_vec machin, t_vec bidule);
float			find_dist(t_vec origin, t_vec ray, t_tg shape, t_rtx rtx);

void			ft_putnbr(int nb);
void			ft_putstr(char *str);
void			init_lst(int fd, t_rtx *rtx);

t_vec			xfois(t_vec truc, float a);
t_vec			normalize(t_vec vect);
t_vec			fois(t_vec truc, float a);
t_vec			min(t_vec truc, t_vec machin);
t_vec			plus(t_vec truc, t_vec machin);
t_vec			cross(t_vec machin, t_vec bidule);

t_color			lfois(t_color color, float a);
t_color			color_init(int r, int g, int b);
t_color			color_add(t_color base, t_color add, float coef);
t_color			color_cap(t_color color, t_color max);

#endif
