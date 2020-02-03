/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:19:08 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/01 12:05:51 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_matrix	init_matrix(t_vec a, t_vec b, t_vec c)
{
	t_matrix matrix;

	matrix.a = a;
	matrix.b = b;
	matrix.c = c;
	return (matrix);
}

t_vec		vec_matrixed(t_vec v, t_matrix m)
{
	t_vec ret;

	ret.x = m.a.x * v.x + m.a.y * v.y + m.a.z * v.z;
	ret.y = m.b.x * v.x + m.b.y * v.y + m.b.z * v.z;
	ret.z = m.c.x * v.x + m.c.y * v.y + m.c.z * v.z;
	return (ret);
}

t_vec		rotate_vec(t_vec base, t_vec rot, float angle)
{
	float		c;
	float		s;
	t_matrix	matrix;

	c = cos(angle);
	s = sin(angle);
	matrix.a = init_vec(rot.x * rot.x * (1 - c) + c, rot.x * rot.y * (1 - c)
	- rot.z * s, rot.x * rot.z * (1 - c) + rot.y * s);
	matrix.b = init_vec(rot.x * rot.y * (1 - c) + rot.z * s, rot.y * rot.y *
	(1 - c) + c, rot.y * rot.z * (1 - c) - rot.x * s);
	matrix.c = init_vec(rot.x * rot.z * (1 - c) - rot.y * s, rot.y * rot.z *
	(1 - c) + rot.x * s, rot.z * rot.z * (1 - c) + c);
	base = vec_matrixed(base, matrix);
	return (base);
}
