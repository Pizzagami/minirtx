/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:43:17 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/05 13:57:32 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

#include "minirtx.h"

void			tri_vecs(t_tg *shape);
float			dot(t_vec machin, t_vec bidule);
float   		dist_dot(t_vec machin, t_vec bidule);
float	        cal_lite_inter(t_rtx rtx, t_light *li, t_vec ptx, t_tg shape);
t_res	        init_res(int x, int y);
t_vec			normalize(t_vec vect);
t_vec			fois(t_vec truc, float a);
t_vec			min(t_vec truc, t_vec machin);
t_vec			plus(t_vec truc, t_vec machin);
t_vec           vec_matrixed(t_vec v, t_matrix m);
t_vec			cross(t_vec machin, t_vec bidule);
t_vec		    init_vec(float x, float y, float z);
t_vec   		rotate_vec(t_vec base, t_vec rot, float angle);
t_vec           find_normal(t_tg shape, t_cam cam, float dist);
t_matrix        init_matrix(t_vec a, t_vec b, t_vec c);
t_color			lfois(t_color color, float a);

int		    	second_degre(t_vec v, float *x1, float *x2);

#endif