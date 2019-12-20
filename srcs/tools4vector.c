/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:18:20 by braimbau          #+#    #+#             */
/*   Updated: 2019/12/20 05:50:13 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_vec	normalize(t_vec vec)
{
	t_vec tmp;

	tmp = vec;
	vec.x /= sqrtf(dot(tmp, tmp));
	vec.y /= sqrtf(dot(tmp, tmp));
	vec.z /= sqrtf(dot(tmp, tmp));
	return(vec);
}

t_vec	min(t_vec truc, t_vec machin)
{
	truc.x -= machin.x;
	truc.y -= machin.y;
	truc.z -= machin.z;

	return (truc);
}

t_vec	plus(t_vec truc, t_vec machin)
{
	truc.x += machin.x;
	truc.y += machin.y;
	truc.z += machin.z;
	return (truc);
}

t_vec	fois(t_vec truc, float a)
{
	truc.x *= a;
	truc.y *= a;
	truc.z *= a;
	return (truc);
}

void	corners(t_tg *shape)
{
	t_vec v1;
	t_vec v2;

	shape->hi /= 2;
	v1.y = 0;
	v1.x = (shape->vec.z == 0) ? 0 : 1;
	v1.z = (shape->vec.x == 0 && v1.x == 1) ? 0 : 1;
	v1.z = (shape->vec.x && shape->vec.z)? -shape->vec.x / shape->vec.z: v1.z;
	v1 = normalize(v1);
	v2 = normalize(cross(shape->vec, v1));

	shape->p1.x = shape->hi * (v1.x + v2.x) + shape->center.x;
	shape->p1.y = shape->hi * (v1.y + v2.y) + shape->center.y;
	shape->p1.z = shape->hi * (v1.z + v2.z) + shape->center.z;
	shape->p2.x = shape->hi * (v1.x - v2.x) + shape->center.x;
	shape->p2.y = shape->hi * (v1.y - v2.y) + shape->center.y;
	shape->p2.z = shape->hi * (v1.z - v2.z) + shape->center.z;
	shape->p3.x = shape->hi * -(v1.x + v2.x) + shape->center.x;
	shape->p3.y = shape->hi * -(v1.y + v2.y) + shape->center.y;
	shape->p3.z = shape->hi * -(v1.z + v2.z) + shape->center.z;
	shape->p4.x = shape->hi * (-v1.x + v2.x) + shape->center.x;
	shape->p4.y = shape->hi * (-v1.y + v2.y) + shape->center.y;
	shape->p4.z = shape->hi * (-v1.z + v2.z) + shape->center.z;
//	printf("-----------\n");
//	print_vecs(4, shape->p1, shape->p2, shape->p3, shape->p4);
//	printf("-----------\n");

}