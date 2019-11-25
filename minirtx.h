/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:10:53 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/25 17:44:17 by braimbau         ###   ########.fr       */
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

int rgbtoon(int r, int g, int b, float o);
t_vec	min(t_vec truc, t_vec machin);
t_vec normalize(t_vec vect);
float dot(t_vec machin, t_vec bidule);
int second_degre(float a, float b, float c, float *x1, float *x2);


#endif