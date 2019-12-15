/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:18:20 by braimbau          #+#    #+#             */
/*   Updated: 2019/12/15 19:26:13 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_vec	normalize(t_vec vect)
{
	t_vec tmp;

	tmp = vect;
	vect.x = vect.x / sqrtf(dot(tmp, tmp));
	vect.y = vect.y / sqrtf(dot(tmp, tmp));
	vect.z = vect.z / sqrtf(dot(tmp, tmp));
	return(vect);
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

t_vec	corners(t_tg *shape)
{
	t_vec v1;
	t_vec v2;

	shape->hi /= 2;
	v1.x = 1;
	v1.y = 0;
	v1.z = -shape->vec.x / shape->vec.z;
	v2 = cross(shape->vec, v1);
	v1 = plus(v1,v2);
	shape->p1.x = sqrt(2 * pow(shape->hi, 2)) * v1.x + shape->center.x;
	shape->p1.y = sqrt(2 * pow(shape->hi, 2)) * v1.y + shape->center.y;
	shape->p1.z = sqrt(2 * pow(shape->hi, 2)) * v1.z + shape->center.z;
	shape->p2.x = sqrt(2 * pow(shape->hi, 2)) * -v1.x + shape->center.x;
	shape->p2.y = sqrt(2 * pow(shape->hi, 2)) * -v1.y + shape->center.y;
	shape->p2.z = sqrt(2 * pow(shape->hi, 2)) * -v1.z + shape->center.z;
	return(v1);
}