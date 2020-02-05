/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:18:11 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/03 11:18:35 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void		corners(t_tg *shape)
{
	shape->hi /= 2;
	shape->p1 = plus(fois(plus(shape->v1, shape->v2),
	shape->hi), shape->center);
	shape->p2 = plus(fois(min(shape->v1, shape->v2),
	shape->hi), shape->center);
	shape->p3 = plus(fois(plus(shape->v1, shape->v2),
	-shape->hi), shape->center);
	shape->p4 = plus(fois(min(shape->v2, shape->v1),
	shape->hi), shape->center);
	shape->hi *= 2;
}

void		find_vecs(t_tg *shape)
{
	if (fabsf(shape->vec.x) <= fabsf(shape->vec.y) &&
		(fabsf(shape->vec.x) <= fabsf(shape->vec.z)))
	{
		shape->v1.x = 1;
		shape->v1.y = 0;
		shape->v1.z = (shape->vec.z != 0) ? -shape->vec.x / shape->vec.z : 0;
	}
	else if (fabsf(shape->vec.z) <= fabsf(shape->vec.y) &&
		(fabsf(shape->vec.z) <= fabsf(shape->vec.x)))
	{
		shape->v1.z = 1;
		shape->v1.y = 0;
		shape->v1.x = (shape->vec.x != 0) ? -shape->vec.z / shape->vec.x : 0;
	}
	else if (fabsf(shape->vec.y) <= fabsf(shape->vec.x) &&
		(fabsf(shape->vec.x) <= fabsf(shape->vec.z)))
	{
		shape->v1.y = 1;
		shape->v1.x = 0;
		shape->v1.z = (shape->vec.z != 0) ? -shape->vec.y / shape->vec.z : 0;
	}
	shape->v1 = normalize(shape->v1);
	shape->v2 = normalize(cross(shape->vec, shape->v1));
}
