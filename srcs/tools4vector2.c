/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4vector2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:19:08 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/19 16:44:15 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

float	dot(t_vec machin, t_vec bidule)
{
	return(machin.x * bidule.x + machin.y * bidule.y + machin.z * bidule.z);
}

t_vec   cross(t_vec machin, t_vec bidule)
{
    t_vec truc;

    truc.x = machin.y * bidule.z - machin.z * bidule.y;
    truc.y = machin.z * bidule.x - machin.x * bidule.z;
    truc.z = machin.x * bidule.y - machin.y * bidule.x;
	return(truc);
}

float   dist_dot(t_vec machin, t_vec bidule)
{
	return(sqrtf(pow(machin.x - bidule.x, 2) +
				pow(machin.y - bidule.y, 2) +
				pow(machin.z - bidule.z, 2)));
}

t_matrix	init_matrix(t_vec a, t_vec b, t_vec c)
{
	t_matrix matrix;

	matrix.a = a;
	matrix.b = b;
	matrix.c = c;
	return(matrix);
}

t_vec		vec_matrixed(t_vec v, t_matrix m)
{
	t_vec ret;
	
	ret.x = m.a.x * v.x + m.a.y * v.y + m.a.z * v.z;
	ret.y = m.b.x * v.x + m.b.y * v.y + m.b.z * v.z;
	ret.z = m.c.x * v.x + m.c.y * v.y + m.c.z * v.z;
	return(ret);
}

t_vec		init_vec(float x, float y, float z)
{
	t_vec vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return(vec);
}