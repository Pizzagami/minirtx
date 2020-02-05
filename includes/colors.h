/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:55:29 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/05 13:57:21 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

#include "minirtx.h"

void            filter(char filter, t_res res, char **id);
void			damier(t_vec point, t_tg *shape, t_color *color);
t_color			color_init(int r, int g, int b);
t_color         cp(int x, int y, char *id, t_res res);
t_color			color_cap(t_color color, t_color max);
t_color         cosha(float ratio, t_color light, t_color shape);
t_color			color_add(t_color base, t_color add, float coef);
t_color		    cm(t_color c1, t_color c2, t_color c3, t_color c4);
t_color         color_mix(t_color c1, t_color c2, float r1, float r2);

#endif