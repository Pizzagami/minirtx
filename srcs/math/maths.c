/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:17:38 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:57:23 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int			second_degre(t_vec v, float *x1, float *x2)
{
	float d;

	if (v.x == 0)
	{
		*x1 = -v.z / v.y;
		return (1);
	}
	d = pow(v.y, 2) - 4 * v.x * v.z;
	if (d < 0)
		return (0);
	else if (d == 0)
	{
		*x1 = -v.y / (2 * v.x);
		return (1);
	}
	else
	{
		*x1 = (-v.y + sqrt(d)) / (2 * v.x);
		*x2 = (-v.y - sqrt(d)) / (2 * v.x);
		return (2);
	}
}

t_vec		find_normal(t_tg shape, t_cam cam, float dist)
{
	t_vec point;
	t_vec normal;

	point = plus(cam.origin, fois(cam.ray, dist));
	if (shape.type == 1 || shape.type == 11)
		normal = normalize(min(point, shape.center));
	else if (shape.type == 21 || shape.type == 32)
	{
		shape.v2 = (dot(shape.vec, min(point, shape.center)) < 0) ?
		fois(shape.vec, -1) : shape.vec;
		shape.v1 = plus(fois(shape.v2, dist_dot(point, shape.center) /
		cos(shape.dia)), shape.center);
		normal = normalize(min(point, shape.v1));
	}
	else if (shape.type == 2)
		normal = normalize(min(point, plus(shape.center, fois(shape.vec,
		dot(min(point, shape.center), shape.vec)))));
	else
		normal = shape.normal;
	return (normal);
}

void		create_tri(t_vec p1, t_vec p2, t_vec p3, t_rtx *rtx)
{
	t_tg *shape;
	t_tg tmp;

	tmp = *(rtx->shape);
	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 3;
	rtx->shape->trans = tmp.trans;
	rtx->shape->refl = tmp.refl;
	rtx->shape->color = tmp.color;
	rtx->shape->p1 = p1;
	rtx->shape->p2 = p2;
	rtx->shape->p3 = p3;
	rtx->shape->dam = tmp.dam;
	shape->normal = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	shape->center = shape->p1;
}
