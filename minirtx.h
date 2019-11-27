/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:10:53 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/27 12:06:58 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRTX_H
# define MINIRTX_H

#include <mlx.h>
#include <math.h>
#include <stdio.h>

typedef struct	s_vec
{
	float x;
	float y;
	float z;
}				t_vec;

int rgbtoon(int r, int g, int b);
t_vec	min(t_vec truc, t_vec machin);
t_vec normalize(t_vec vect);
float dot(t_vec machin, t_vec bidule);
int second_degre(float a, float b, float c, float *x1, float *x2);
float find_dist(t_vec ray, t_vec origin, t_vec center, int r);
int ft_atoi(char *str);
t_vec	plus(t_vec truc, t_vec machin);
t_vec	fois(t_vec truc, float a);
#endif